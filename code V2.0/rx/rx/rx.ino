#include <TMRpcm.h>
#include <pcmConfig.h>
#include <pcmRF.h>
#include "SD.h"
#include "TMRpcm.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Adafruit_GFX.h> 
#include <Adafruit_TFTLCD.h> 
#include "Arduino.h"
#include <Wire.h>
int msg[4];
int BLE[1]={0};
#define LCD_CS A3
#define LCD_CD A2 
#define LCD_WR A1 
#define LCD_RD A0 
#define LCD_RESET A4 
#define SD_ChipSelectPin 49
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
RF24 radio(48,53);
TMRpcm tmrpcm;
const uint64_t pipe2 = 0xE8E8F0F0E2LL;
const uint64_t pipe3 = 0xE8E8F0F0E3LL;
void setup() {
Serial.begin(9600);
Wire.begin();
radio.begin();
radio.openWritingPipe(pipe3);
radio.setPALevel(RF24_PA_LOW);
radio.setDataRate(RF24_250KBPS);
uint16_t identifier = tft.readID();  
tft.begin(identifier); 
SD.begin(49);
tmrpcm.speakerPin = 11;
}

void loop () { 
tft.fillScreen(BLACK);  
tft.setCursor(0, 0);
tft.setTextColor(RED); 
tft.setTextSize(3);  
tmrpcm.setVolume(4);
rad();   
if((msg[0]>=12)&&(msg[0]<=18)&&(msg[1]>=17)&&(msg[1]<=22))// Sorry
{
tft.println("Sorry");
tmrpcm.play("s.wav");
  BLE[0]=6;
  radio.stopListening(); 
   radio.write(&BLE,sizeof(BLE)); 
   delay(100); 
}

else if((msg[0]>=20)&&(msg[0]<=22)&&(msg[1]>=4)&&(msg[1]<=14)) // hello
{
  tft.println("hello");
  BLE[0]=1;
  radio.stopListening(); 
    radio.write(&BLE,sizeof(BLE)); 
    delay(100);
}

else if((msg[0]>=17)&&(msg[0]<=22)&&(msg[1]>=19)&&(msg[1]<=26))  // thank you 
{
tft.println("Thank You");
tmrpcm.play("t.wav");
BLE[0]=2;
radio.stopListening(); 
    radio.write(&BLE,sizeof(BLE)); 
    delay(100);
}

else if((msg[0]>=19)&&(msg[0]<=23)&&(msg[1]>=-4)&&(msg[1]<=1))  // welcome
{
tft.println("Welcome");
tmrpcm.play("w.wav");
BLE[0]=3;
radio.stopListening(); 
   radio.write(&BLE,sizeof(BLE)); 
   delay(100);
}

else if((msg[0]>=15)&&(msg[0]<=20)&&(msg[1]>=17)&&(msg[1]<=20)&&(msg[2]>=36)&&
(msg[2]<=40)&&(msg[3]>=2)&&(msg[3]<=6))// help

{
 tft.println("Help");
tmrpcm.play("h.wav");
  BLE[0]=4;
  radio.stopListening(); 
    radio.write(&BLE,sizeof(BLE)); 
    delay(100);
}

else if((msg[0]>=17)&&(msg[0]<=20)&&(msg[1]>=12)&&(msg[1]<=17)&&(msg[2]>=34)&&
(msg[2]<=37)&&(msg[3]>=4)&&(msg[3]<=12))  // close
{
  tft.println("Close");
tmrpcm.play("c.wav");
  BLE[0]=5;
  radio.stopListening(); 
    radio.write(&BLE,sizeof(BLE)); 
    delay(100);
    
}
else
{
  tft.println("Invalid Sign");
  BLE[0]=7;
  radio.write(&BLE,sizeof(BLE)); 
  delay(100);
}

}
void rad (){
  radio.startListening();
radio.openReadingPipe(1,pipe2);
if(radio.available()) {  
radio.read(&msg,sizeof(msg)); 
Serial.println(msg[0]);
Serial.println(msg[1]);
Serial.println(msg[2]);
Serial.println(msg[3]);
}}

