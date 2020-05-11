#include<Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>

const int MPU_ADDR = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
int time_seq = 0;

//자이로, 릴레이 핀번호
//자이로 SCL:22, SDA:21
const int relay_sig=15;
const int gyro_vlt=23;
const int gyro_gnd=19;

double angleAcX, angleAcY, angleAcZ;
double angleGyX, angleGyY, angleGyZ;
double angleFiX, angleFiY, angleFiZ;

const double RADIAN_TO_DEGREE = 180 / 3.14159;
const double DEGREE_PER_SECOND = 32767 / 250;
const double ALPHA = 1 / (1 + 0.04);

unsigned long now = 0;
unsigned long past = 0;

double dt = 0;
double baseAcX, baseAcY, baseAcZ;
double baseGyX, baseGyY, baseGyZ;


// WIFI setting
const char* ssid="U+NetD913";
const char* password="4000015816";

String Url = "http://ec2-54-180-101-207.ap-northeast-2.compute.amazonaws.com:8083/degree?x=";

void setup() {

  pinMode(gyro_vlt, OUTPUT);
  digitalWrite(gyro_vlt, 1);
  pinMode(gyro_gnd, OUTPUT);
  digitalWrite(gyro_gnd, 0);
  
  pinMode(relay_sig, OUTPUT);
  
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Connecting to WiFi...");
   }
   Serial.println("Connected!!");
   
  initSensor();
  calibrateSensor();
  past = millis();
}

void loop() {
  time_seq = (time_seq + 1) % 1000;
  
  getData();
  getDT();
  double angleTmp;
  HTTPClient http;

//user_id 설정
//1:PARK 2:JEON 3:KIM
  int user_id=1;
  
  
//x
  angleAcX = atan(-AcY / sqrt(pow(AcX, 2) + pow(AcZ, 2)));
  angleAcX *= RADIAN_TO_DEGREE;

  angleGyX = ((GyX - baseGyX) / DEGREE_PER_SECOND) * dt;

  angleTmp = angleFiX + angleGyX * dt;
  angleFiX = ALPHA * angleTmp + (1.0 - ALPHA) * angleAcX;
  Serial.printf("X: %f", angleFiX);

//y
  angleAcY = atan(-AcX / sqrt(pow(AcY, 2) + pow(AcZ, 2)));
  angleAcY *= RADIAN_TO_DEGREE;

  angleGyY = ((GyY - baseGyY) / DEGREE_PER_SECOND) * dt;

  angleTmp = angleFiY + angleGyY * dt;
  angleFiY = ALPHA * angleTmp + (1.0 - ALPHA) * angleAcY;
  Serial.printf("  Y: %f\n", angleFiY);

  if (!time_seq) {
    double temp=(-1)*angleFiY; //y각도 양수로 바꿔줌

    if(angleFiX>-15 && angleFiX<15 && angleFiY<-80){
     Serial.printf(" normal!!!!\n");
     digitalWrite(relay_sig, 0);   
    }
    else{
     Serial.printf(" trash!!!!\n");
     digitalWrite(relay_sig, 1); 
    }
    
    http.begin(Url + angleFiX + "&y=" + temp + "&xa=" + AcX + "&ya=" + AcY + "&id=" + user_id);
    http.GET();
  }
}

void initSensor() {
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

void getData() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true);

  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  Tmp = Wire.read() << 8 | Wire.read();
  GyX = Wire.read() << 8 | Wire.read();
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();
}

void getDT() {
  now = millis();
  dt = (now - past) / 1000.0;
  past = now;
}

void calibrateSensor() {
  double sumAcX = 0, sumAcY = 0, sumAcZ = 0;
  double sumGyX = 0, sumGyY = 0, sumGyZ = 0;
  getData();
  for (int i = 0; i < 10 ; i++) {
    getData();
    sumAcX += AcX; sumAcY += AcY; sumAcZ += AcZ;
    sumGyX += GyX; sumGyY += GyY; sumGyZ += GyZ;
    delay(100);
  }
  baseAcX = sumAcX / 10;
  baseAcY = sumAcY / 10;
  baseAcZ = sumAcZ / 10;
  baseGyX = sumGyX / 10;
  baseGyY = sumGyY / 10;
  baseGyZ = sumGyZ / 10;
}
