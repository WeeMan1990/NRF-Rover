
/*
 * Pinout for MDD3A Cytron Motor driver
 * M1A - D6 - White
 * M1B - D9 - Green
 * M2A - D5 - Red
 * M2B - D3 - Yellow
 * GND - GND - Black
 * 
 * NRF24L01 Pinout: 
 * VCC - 3V 
 * GND - GND 
 * CNS - D7
 * CE  - D8 
 * MOSI - D11
 * MISO - D12 
 * SCK  - D13
 */
#include "SPI.h"                              
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"
#include "CytronMotorDriver.h"
#include <Servo.h> //TEST FÖR SERVO! 

CytronMD motor1(PWM_PWM, 6, 9);  //RIGHT SIDE MOTOR - PIN D6 = M1A - WHITE || PIN D9 = M1B - GREEN
CytronMD motor2(PWM_PWM, 3, 5);  //LEFT  SIDE MOTOR - PIN D3 = M2B - YELLOW || PIN D5 = M2A - RED
Servo servo1; //Servo 1 for camera Pan/Tilt
Servo servo2; //Servo 2 for camera Pan/Tilt

int data;
int a; 
int b; 
int s1;
int s2;

void setup(){  
  Mirf.spi = &MirfHardwareSpi;      
  Mirf.init();
  Mirf.setRADDR((byte *)"serv1");  //Set transmitter adress equally! 
  Mirf.payload = sizeof(int);      
      Mirf.config(); 
      //Camera pan/tilt is adjusted by moving the controller sticks sideways
      servo1.attach(4); //LEFT STICK VERTICAL CAMERA MOVEMENT
      servo2.attach(2); //RIGHT STICK HORIZONTAL CAMERA MOVEMENT
      Serial.begin(9600);
     
}

void loop(){
  if(Mirf.dataReady()){              //Execute if data is received
      Mirf.getData((byte *)&data);   //receive data
      //CHANNEL 1 - LEFT SIDE MOTOR - M2A/M2B-----------------------------------          
      if (data>=0&&data<=999)                
      {   
      a=map(data,0,999,-255,255);
      if (a<-31||a>2) //Calibration for LEFT controller stick dead center. 
    {
     motor2.setSpeed(a);
      }
      else
{ 
    motor2.setSpeed(0);
  }
}
      //CHANNEL 2 - RIGHT SIDE MOTOR - M1A/M1B-----------------------------------
      if (data>=1000&&data<=1999)
      {
      b=map(data,1000,1999,-255,255);
      if (b<-31||b>2) //Calibration for RIGHT controller stick dead center. 
    {
     motor1.setSpeed(b);
      }
      else
    { 
    motor1.setSpeed(0);
  }
}
//CHANNEL-3-SERVO-VERTICAL- PIN D4
if (data>=2000&&data<=2999)
s1 = map(data, 2000, 2999, 700, 2000); //The 4th value (700) sets center position for servo
servo1.write(s1);
//CHANNEL-4-SERVO-HORIZONTAL-PIN D2
if (data>=3000&&data<=3999)
s2 = map(data, 3000, 3999, 730, 2300); //The 4th value (730) sets center position for servo
servo2.write(s2);
    
//Used for debugging: 
//Serial.println(data);
//Serial.print("Set speed A - LEFT MOTOR (M2) - ");
//Serial.println(a);
//Serial.print("Set speed B - RIGHT MOTOR (M1) - ");
//Serial.println(b);
//Serial.print("Servo 1 VERTICAL - "); 
//Serial.println(s1);
//Serial.print("Servo 2 HORIZONTAL - "); 
//Serial.println(s2);
//Serial.print("aa");
//Serial.println(c);
    
  }
}
