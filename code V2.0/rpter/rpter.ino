#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>  
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SoftwareSerial.h>
int BLE[1]={0};
Adafruit_MPU6050 mpu;
SoftwareSerial bl(7,8);
RF24 radio(9,10); 
const uint64_t pipe1 = 0xE8E8F0F0E1LL;
const uint64_t pipe2 = 0xE8E8F0F0E2LL;
const uint64_t pipe3 = 0xE8E8F0F0E3LL;
const int flexPin0 =A0; 
const int flexPin1= A1; 
const int flexPin2= A2; 
const int flexPin3= A3; 
const int flexPin4= A6;
int MPU[6];
int msg [4];
int Value[7];
void setup() {

      Serial.begin(115200);
      bl.begin(115200);
      radio.begin();
      radio.openReadingPipe(1,pipe1);
      radio.openWritingPipe(pipe2);
      radio.setPALevel(RF24_PA_LOW);
      radio.setDataRate(RF24_250KBPS);
      smpu();
       }

void loop () { 
 radio.startListening(); 
if(radio.available()){ 
 radio.read(msg,sizeof(msg));}
 delay(50);
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
msg[2] =((flexValue0+flexValue1+flexValue2+flexValue3+flexValue4)/5)*0.2 ;

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
    msg[3] =(((MPU[0]*2+MPU[1]*2+MPU[2]*2+MPU[3]*2+MPU[4]*2+MPU[5]*2)*10)/6)*0.5 ; 
  
    delay(50);
    radio.stopListening(); 
    radio.write(&msg,sizeof(msg)); 
    


    radio.openReadingPipe(1,pipe3);
    radio.startListening();
    rad(); 

    delay(300);

    // while(BLE[0]==0);

    if(BLE[0]==6)//Sorry
    {
      send_string("Sorry");
      BLE[0]=0;
    }

    else if (BLE[0]==1) //Hello
    {
      send_string("Hello");
      BLE[0]=0;
    }
   else if (BLE[0]==2) //Thank You
    {
      send_string("Thank You");
      BLE[0]=0;
    }
   else if (BLE[0]==3) //Welcome
    {
      send_string("Welcome");
      BLE[0]=0;
    }
       else if (BLE[0]==4) //Help
    {
      send_string("Help");
      BLE[0]=0;
    }
       else if (BLE[0]==5) //Close
    {
      send_string("Close");
      BLE[0]=0;
    }
    else
    {
      send_string("Invalid Sign");
      BLE[0]=0;
    }
    radio.openReadingPipe(1,pipe1);
}



void smpu(){
 Serial.begin(115200);
  while (!Serial)
    delay(10); 
  if (!mpu.begin()) {
      delay(10);
    }
  mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
  mpu.setMotionDetectionThreshold(1);
  mpu.setMotionDetectionDuration(20);
  mpu.setInterruptPinLatch(true);	
  mpu.setInterruptPinPolarity(true);
  mpu.setMotionInterrupt(true);
}


void send_string(u8* Coby_U8String){

  int i = 0;
  
  String send_data =Coby_U8String;
  
  int number_of_data = send_data.length();
  
  while (i < number_of_data){
      
      char one_alphabet = send_data[i];

      bl.write(one_alphabet);

      Serial.print(one_alphabet);

     i++ ;
  }
  
  // Serial.println("");
  delay(1000);
  
}
void rad (){
if(radio.available()) {  
radio.read(&BLE,sizeof(BLE)); 

}}

