역학센서를 이용한 허리 밸런스 유지 장치
========================================

팀명 : 두통치통보다 요통 (제품명 : 허리업)
------------------------

항상 허리가 아픈 현대인을 위해서..
 
우리 몸의 대들보인 허리!  현대인들의 허리 건강에 적신호가 켜졌다!
-------------------------------------------------------------
   * 인구 고령화로 인해서 요통 환자들이 늘고 있다.
    <center><img src="images/yo.jpg" width="80%" height="80%" title="News" alt="News"></center></img>
    <center><img src="images/yo1.jpg" width="80%" height="80%" title="News" alt="News"></center></img>
    
어떻게 해결하고 있을까?
----------------------
   * 다음은 허리의 부담을 완화해주는 허리 보호대를 착용하여 해결하고 있는 모습이다.
    <center><img src="images/news.jpg" width="60%" height="60%" title="News" alt="News"></center></img>
    
복대의 단점
----------
   <center><img src="images/news_3.png" width="60%" height="60%" title="News" alt="News"></center></img>
   * 일시적인 착용은 허리의 부담을 덜어줄 수 있지만, 장시간 의존하게 되면 복근과 기립근이 약해져 또 다른 통증을 유발한다! <br/>
   
   ### 뒤틀어진 자세 
   * 척추 측만증과 허리디스크를 초래할 수 있다.<br/>
   * 하지만, 자신의 자세가 올바른지 확인할 방법이 없다!<br/>
   
해결 방안
---------
  * 복대의 압력을 상황에 맞게 조절한다면? <br/>
    복대 의존도를 낮춤으로써, 근육 약화를 방지할 수 있다!
  * 자신의 자세를 모니터링할 수 있다면? <br/>
    자신의 문제점을 파악함으로써 올바른 자세로 교정할 수 있다!
  
프로젝트 설명
------------
  <center><img src="images/system_image.jpg" width="80%" height="70%" title="System" alt="System"></center></img><br>
  
  <center><img src="images/arduino_circuit5_30.jpg" width="50%" height="40%" title="Arduino" alt="Arduino"></center></img><br>
  
  ### 자동 조절 시스템
  1. 복대에 부착된 센서(MPU6050)로부터 사용자의 자세를 추정한다.
  2. LSTM 모델을 이용하여, 사용자가 취하게 될 허리 각도를 예측한다.
  3. 예측한 허리 각도와 현재 허리 각도를 통해 자세를 추정한다.
  4. 해당 자세에 맞는 압력을 제공한다.<br><br>
  
  ### 커스터마이징
  1. FSR-402를 이용하여, 사용자가 받는 복대압을 측정한다.
  2. 사용자의 체형이 다르더라도 동일한 압력을 받을 수 있다.<br><br>
  
  ### 자세 모니터링 시스템
  1. 1분 간격으로 센서 데이터를 Database에 누적시킨다.
  2. Web Server에서 Database 값을 이용하여 추정한 사용자의 자세를 볼 수 있게 한다.
  3. 현재 사용자의 자세가 허리에 어떤 부담을 주는지 이미지를 통해 알려준다.
  
제품 이미지
----------
### Web 이미지
<center><img src="images/web_image.jpg" width="80%" height="80%" title="News" alt="News"></center></img>
http://54.180.101.207:8081/<br/>
1. 사용자의 허리에 부담이 간 부분을 이미지를 통해 알려준다. <br/>
2. 이 웹사이트를 통해 사용자가 자신의 허리 상태를 알 수 있다. <br/>

### 제품 이미지
<center><img src="images/HurryUp.jpg" width="80%" height="80%" title="News" alt="News"></center></img>
1. 멜빵에 부착된 자이로 센서 MPU6050으로 사용자의 허리 각도를 측정한다. <br/>
2. 허리 커프(복대) 내에 부착되어 있는 압력 센서 FSR-402로 사용자의 허리에 가해진 압력을 측정한다. <br/>
3. 공기배출용 에어펌프(DAP370P)와 공기주입용 에어펌프(DQB370-B2)를 이용하여 복대의 압력을 원하는 만큼 조절한다. <br/>

<br/>

기대 성과
--------
  * 내 몸에 맞는 복대를 찾자!<br>
    머신 러닝으로 학습된 데이터를 기반으로, 내 몸에 딱 맞는 복대를 만들 수 있다.
    
  * 어디에서나 내 자세를 확인하자!<br>
    축적된 신체 데이터를 분석하여 평가해주는 자신의 허리만을 위한 비서를 가질 수 있다.
    
  * 건강한 허리 근육을 되찾자! <br>
    올바른 자세를 유지하고, 허리 건강을 되찾을 수 있다.<br>
<img src="images/change.jpg" width="300px" height="200px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img> <br><br>
  
Team 구성
---------
  * 김주현 (팀장) <br/>
<img src="images/kim.jpg" width="100px" height="100px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img> <br>
    팀장(발표)<br>
    일정(Milestone) 관리<br>
    딥러닝 시스템 구축<br>
    딥러닝 데이터 수집<br>
    기업 벤치마킹<br/><br/>
  * 박영재 (Committer) <br/>
<img src="images/park.jpg" width="100px" height="100px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img> <br>
    데이터베이스 구축<br>
    데이터 가공<br>
    센서 네트워킹<br>
    테스터<br>
    Committer<br/><br/>
  * 전범준 <br/>
<img src="images/jeon.jpg" width="100px" height="100px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img> <br>
    서버 구축<br>
    웹서버 디자인<br>
    서버-데이터베이스간 네트워킹<br>
    에어 펌프 연결<br>
    제품 관리<br/><br/>
  
## 개발환경
  * Arduino (Gyro, Acceleration sensor)
  * MySQL
  * Node.js / Express-Framework
  * Python3.8 (Keras)
  * HTTP / PHP
  * Github (pull request)<br/>
  
  |Date|Event|
  |:------------:|:-------------------:|
  |2020.04.09.|프로젝트 컨셉 회의|
  |2020.04.11.|MD 파일 작성|
  |2020.04.16.|적합한 센서 찾기|
  |2020.04.20.|팀원 화상 회의|
  |2020.04.26.|팀원 임무 구체화|
  |2020.04.30.|팀원 임무 구체화|
  |2020.05.02.|대면회의(서버, DB 구축 및 센서 연동), 시장조사|
  |2020.05.04.|대면 멘토링|
  |2020.05.08.|MPU-6050 테스트|
  |2020.05.15.|에어펌프 연동|
  |2020.05.22.|WiFiManager 구현 및 데이터 수집|
  |2020.05.29.|제품 마무리|
  |2020.06.05.|전략 수립 및 데이터 학습|
  |2020.06.12.|판넬 제작|
  |2020.06.19.|영상, 장표 제작|
