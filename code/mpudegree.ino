#include<Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <esp_wifi.h>
#include <WiFiClient.h>
#include <ESP_WiFiManager.h>

const int MPU_ADDR = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
int time_seq = 0;

//자이로, 릴레이 핀번호
//자이로 SCL:22, SDA:21
const int relay_sig1=26; //input
const int relay_sig2=27;  //vacuum
const int gyro_vlt=23;
const int gyro_gnd=19;
const int switch_vlt=5;
const int switch_gnd=18;
const int switch_sig1=16;
const int switch_sig2=17;
const int fsr_pin=34;
const float VCC = 4.98;
const float R_DIV = 3230.0;

const int err=100;
const int pressure_default=1500;
int pressure;

int fsrADC=0;
int fsr_value=0;

double angleAcX, angleAcY, angleAcZ;
double angleGyX, angleGyY, angleGyZ;
double angleFiX, angleFiY, angleFiZ;
double x_delta, y_delta, x_deltaavg=0, y_deltaavg=0;
double x_temp=0, y_temp=0;

int sit_flag; // 0 : 섬 1: 앉음
int num=0;

//user_id 설정
//1:PARK 2:JEON 3:KIM
int user_id;
  
const double RADIAN_TO_DEGREE = 180 / 3.14159;
const double DEGREE_PER_SECOND = 32767 / 250;
const double ALPHA = 1 / (1 + 0.04);

unsigned long now = 0;
unsigned long past = 0;

double dt = 0;
double baseAcX, baseAcY, baseAcZ;
double baseGyX, baseGyY, baseGyZ;

char id[20] = "Input_user_id";

String Url = "http://ec2-54-180-101-207.ap-northeast-2.compute.amazonaws.com:8083/degree?x=";

void setup() {

  pinMode(gyro_vlt, OUTPUT);
  digitalWrite(gyro_vlt, 1);
  pinMode(gyro_gnd, OUTPUT);
  digitalWrite(gyro_gnd, 0);
  
  pinMode(switch_vlt, OUTPUT);
  digitalWrite(switch_vlt, 1);
  pinMode(switch_gnd, OUTPUT);
  digitalWrite(switch_gnd, 0);
  pinMode(switch_sig1, INPUT);
  pinMode(switch_sig2, INPUT);
  
  pinMode(relay_sig1, OUTPUT);
  pinMode(relay_sig2, OUTPUT);
  
  Serial.begin(115200);

  //wifimanager setting
  ESP_WMParameter custom_id("id", "user_id", id, 21);
  ESP_WiFiManager ESP_wifiManager("HURRYUP_WIFI");
  ESP_wifiManager.addParameter(&custom_id);
  
  String AP_SSID = "HURRYUP_WIFI";
  ESP_wifiManager.autoConnect(AP_SSID.c_str());
  Serial.println("WiFi connected!");

  strncpy(id, custom_id.getValue(), sizeof(id));
  sscanf(id, "%d", &user_id);
   
  initSensor();
  calibrateSensor();
  past = millis();

 digitalWrite(relay_sig1, 1);
 while((fsrADC = analogRead(fsr_pin)) < pressure_default) Serial.println(fsrADC);
 digitalWrite(relay_sig1, 0);
  
}

void loop() {
  time_seq = (time_seq + 1) % 1000;
  
  getData();
  getDT();
  double angleTmp;
  double x_accel;
  double y_accel;
  HTTPClient http;

  if(digitalRead(switch_sig1)==LOW){
    sit_flag=1;
  }
  else if(digitalRead(switch_sig2)==LOW){
    sit_flag=0;
  }

  fsrADC=analogRead(fsr_pin);
  
  if(fsrADC != 0){
   // Serial.println(fsrADC);
   fsr_value=fsrADC;
    float fsrV = fsrADC * VCC / 8000.0;
    float fsrR = R_DIV * (VCC / fsrV - 1.0);
   // Serial.println("Resistance: " + String(fsrR) + " ohms");
    float force;
    float fsrG = 1.0 / fsrR;
    if (fsrR <= 600) 
      force = (fsrG - 0.00075) / 0.00000032639;
    else
      force =  fsrG / 0.000000642857;
   // Serial.println("Force: " + String(force) + " g");
   // Serial.println();
  }
    else {}
  
//x
  angleAcX = atan(-AcY / sqrt(pow(AcX, 2) + pow(AcZ, 2)));
  angleAcX *= RADIAN_TO_DEGREE;

  angleGyX = ((GyX - baseGyX) / DEGREE_PER_SECOND) * dt;

  angleTmp = angleFiX + angleGyX * dt;
  angleFiX = ALPHA * angleTmp + (1.0 - ALPHA) * angleAcX;
  x_accel  = ((GyX - baseGyX) / DEGREE_PER_SECOND);
  //Serial.printf("X: %f", angleFiX);

//y
  angleAcY = atan(-AcZ / sqrt(pow(AcY, 2) + pow(AcX, 2)));
  angleAcY *= RADIAN_TO_DEGREE;

  angleGyY = ((GyY - baseGyY) / DEGREE_PER_SECOND) * dt;

  angleTmp = angleFiY + angleGyY * dt;
  angleFiY = ALPHA * angleTmp + (1.0 - ALPHA) * angleAcY;
  y_accel  = ((GyY - baseGyY) / DEGREE_PER_SECOND);
  //Serial.printf("  Y: %f\n", angleFiY);
  
  if(!(time_seq%100)){
//0.1초전 값과의 차이
   x_delta = angleFiX - x_temp;
   y_delta = angleFiY - y_temp;  

   x_deltaavg += x_delta;
   y_deltaavg += y_delta;
   num += 1;
  
//0.1초전 값
   x_temp = angleFiX;
   y_temp = angleFiY;
  }

  int target;
  if (!time_seq) {
    double temp = angleFiY; //y각도 양수로 바꿔줌
    x_deltaavg = x_deltaavg/(double)num;
    y_deltaavg = y_deltaavg/(double)num;

  if(sit_flag==0){
      if(angleFiX>-15 && angleFiX<15 && angleFiY<10 && angleFiY>-10){
      Serial.printf(" normal!!!!X_angle: %f\n Y_angle: %f\nfsr: %d\nsit_flag: %d\n",angleFiX, angleFiY, fsr_value, sit_flag);
      target=0;
     }
     else if(angleFiY<20 && angleFiY>-20){
      Serial.printf(" level1!!!!X_angle: %f\n Y_angle: %f\nfsr: %d\nsit_flag: %d\n",angleFiX, angleFiY, fsr_value, sit_flag);
      target=5000;
     }
     else{
      Serial.printf(" level2!!!!X_angle: %f\n  Y_angle: %f\nfsr: %d\nsit_flag: %d\n",angleFiX, angleFiY, fsr_value, sit_flag);
      target=10000;
     }
  }
  else{
   if(angleFiX>-10 && angleFiX<10 && angleFiY<20 && angleFiY>-10){
      Serial.printf(" normal!!!!X_angle: %f\n Y_angle: %f\nfsr: %d\nsit_flag: %d\n",angleFiX, angleFiY, fsr_value, sit_flag);
      target=0;    
   }
   else if(angleFiX>-15 && angleFiX<15 && angleFiY<30 && angleFiY>-20){
      Serial.printf(" normal!!!!X_angle: %f\n Y_angle: %f\nfsr: %d\nsit_flag: %d\n",angleFiX, angleFiY, fsr_value, sit_flag);
      target=5000;    
   }
   else {
      Serial.printf(" level2!!!!X_angle: %f\n  Y_angle: %f\nfsr: %d\nsit_flag: %d\n",angleFiX, angleFiY, fsr_value, sit_flag);
      target=10000;    
   }
  }
    
    http.begin(Url + angleFiX + "&y=" + temp + "&xa=" + x_accel + "&ya=" + y_accel + "&id=" + user_id + "&xd=" + x_delta + "&yd=" + y_delta + "&xda=" + x_deltaavg + "&yda=" + y_deltaavg + "&sit=" + sit_flag);
    http.GET();

    num=0;
    x_deltaavg=0;
    y_deltaavg=0;
  }


  if (pressure < target - err) {
    pressure += 2;
    digitalWrite(relay_sig1, HIGH);
    digitalWrite(relay_sig2, LOW);
  }
  else if (pressure >= target + err) {
    pressure--;
    digitalWrite(relay_sig1, LOW);
    digitalWrite(relay_sig2, HIGH);
  }
  else {
    digitalWrite(relay_sig1, LOW);
    digitalWrite(relay_sig2, LOW);
  }

/* Debug
  if (sit_flag) {
    digitalWrite(relay_sig1, HIGH);
    digitalWrite(relay_sig2, LOW);
  }
  else {
    digitalWrite(relay_sig1, LOW);
    digitalWrite(relay_sig2, HIGH);
  }
*/
  
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
