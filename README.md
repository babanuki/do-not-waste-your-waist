역학센서를 이용한 허리 밸런스 유지 장치
========================================

팀명 : 두통치통보다요통
------------------------

항상 허리가 아픈 현대인을 위해서..

### 문제인식


   * 올바르지 못한 자세로 인해, 현대인들의 허리 부담이 증가
   * 요통 관련 환자의 증가
    ![Alt text](/yo.jpg)
    ![Alt text](/yo1.jpg)
   * 복대의 문제점
    ![Alt text](/bok.jpg)
    ![Alt text](/bok1.jpg)
 
    
### Painpoint
##### 뒤틀어진 자세
   * 척추 측만증, 허리디스크를 유발 / 악화
   * 자신의 현재 자세가 올바른지 확인할 방법이 부족
##### 복대의 단점
   * 일시적 착용은 허리 부담을 덜어주는데, 장시간 착용시 복근과 기립근이 약해져 또 다른 통증을 유발
   
### 해결 방안
  * 사용자의 자세를 자이로 센서를 이용해 지속적으로 모니터링 하여, 자세가 올바르지 않을 때 경고 신호를 준다.
  * 에어 펌프를 이용하여, 경고 신호가 발생했을 때에 복대의 기능을 적용할 수 있도록 한다.
  
### 시스템 구성도
  사진
  
### 구현 방법
  1. 자세 모니터링 : 자이로 센서, 가속도 센서
  2. 센서 -> 서버 : 현재 센서값을 전송
  3. 서버에서, 신체의 운동에 의한 허리의 각속도/각도를 토대로 자세를 추정
  4. 해당 자세를 분석하여 압력 레벨을 결정
  5. 계산된 레벨을 에어펌프에 전송 / 작동 (DAP-370P)
  6. 너무 강하거나 약하면, 사용자가 임의 설정가능
  7. 설정 데이터가 바뀌면 해당 데이터를 다시 DB에 보내서 재학습
  
### 성과
  복대의 장점만을 살려서, 직관적인 보조작동을 가능케한다.
  
### Team
  * 김주현
  * 박영재
  * 전범준
  
## 개발환경
  * Arduino (Gyro, Acceleration sensor)
  * MySQL
  * Node.js / Express-Framework
  * Python3.8 (Keras)
  * HTTP / PHP
  
