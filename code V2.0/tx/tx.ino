#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>  
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SoftwareSerial.h>
Adafruit_MPU6050 mpu;
RF24 radio(9,10); 
const uint64_t pipe1 = 0xE8E8F0F0E1LL;
const int flexPin0 =A0; 
const int flexPin1= A1; 
const int flexPin2= A2; 
const int flexPin3= A3; 
const int flexPin4= A6; 
int msg[2];
void setup() {
      Serial.begin(115200);
      radio.begin();
      radio.openWritingPipe(pipe1);
      radio.setPALevel(RF24_PA_LOW);
      radio.setDataRate(RF24_250KBPS);
      radio.stopListening();    
      smpu();
}
void flex_MPU () { 
 int flexValue0 = analogRead(flexPin0);
 int flexValue1= analogRead(flexPin1);
 int flexValue2= analogRead(flexPin2);
 int flexValue3= analogRead(flexPin3);
 int flexValue4= analogRead(flexPin4);
 Serial.println(analogRead(flexPin0));
Serial.println(analogRead(flexPin1));
Serial.println(analogRead(flexPin2));
Serial.println(analogRead(flexPin3));
Serial.println(analogRead(flexPin4));
 msg[0]=((flexValue0+flexValue1+flexValue2+flexValue3+flexValue4)/5)*0.2 ;
  int MPU[6];
if(mpu.getMotionInterruptStatus()) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    MPU[0]=(a.acceleration.x);
    MPU[1]=(a.acceleration.y);
    MPU[2]=(a.acceleration.z);
    MPU[3]=(g.gyro.x);
    MPU[4]=(g.gyro.y);
    MPU[5]=(g.gyro.z);   
    
  }
  msg[1]=(((MPU[0]*2+MPU[1]*2+MPU[2]*2+MPU[3]*2+MPU[4]*2+MPU[5]*2)*10)/6)*0.5 ;

  
  }
  void smpu(){
 Serial.begin(115200);
  while (!Serial)
    delay(10); 
  if (!mpu.begin()) {
    while (1) {
      delay(10);
    }
  }
  mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
  mpu.setMotionDetectionThreshold(1);
  mpu.setMotionDetectionDuration(20);
  mpu.setInterruptPinLatch(true);	
  mpu.setInterruptPinPolarity(true);
  mpu.setMotionInterrupt(true);

}
 
void sendmsg(){radio.write(&msg,sizeof(msg));
}

void loop() {flex_MPU();sendmsg();}
   
 
 


