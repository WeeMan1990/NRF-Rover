#include "SPI.h"      
#include "Mirf.h"
#include "nRF24L01.h"+-
#include "MirfHardwareSpiDriver.h"
int a;        //Define a variable to store the previous channel parameters;
int aa;       //Changed channel parameters;
int b;
int bb;
int c;
int cc;
int d;
int dd;
int e;
int ee;
int x = 2; //Switch channel;
int y = 3;
int z = 4;
int f = 4001;
int g = 4002;
int h = 4003;
int i = 4005;
int data;

void setup(){  
  Mirf.spi = &MirfHardwareSpi;      
  Mirf.init();                      
  Mirf.setTADDR((byte *)"serv1");      //Set receiver adress equally! 
  Mirf.payload = sizeof(int);          //Define data type as integer;
  Mirf.config();
  Serial.begin(9600);
  pinMode(x, INPUT);
  pinMode(y, INPUT);
  pinMode(z, INPUT);

}
void loop() {

  a = analogRead(A0);          //Read the LEFT side stick FWD/BACKWARDS motion.
  b = analogRead(A1);          //Read the RIGHT side stick FWD/BACKWARDS motion. 
  c = analogRead(A2);
  d = analogRead(A3);
  e = analogRead(A4);
  a = map(a, 0, 1023, 0, 999) ;      //CHANNEL 1 - LH STICK MOVEMENT UP/DOWN
  b = map(b, 0, 1023, 1000, 1999) ;  //CHANNEL 2 - RH STICK MOVEMENT UP/DOWN
  c = map(c, 0, 1023, 2000, 2999) ;  //CHANNEL 3 - LH STICK MOVEMENT LEFT/RIGHT
  d = map(d, 0, 1023, 3000, 3999) ;  //CHANNEL 4 - RH STICK MOVEMENT LEFT/RIGHT
  e = map(e, 0, 1023, 5000, 5999) ;
  Mirf.send((byte *)&a); //Sending data to the receiver;
  while (Mirf.isSending()) {  
  }
  Mirf.send((byte *)&b);
  while (Mirf.isSending()) {
  }
  Mirf.send((byte *)&c);
  while (Mirf.isSending()) {
  }
  Mirf.send((byte *)&d);
  while (Mirf.isSending()) {
  }
  Mirf.send((byte *)&e);
  while (Mirf.isSending()) {
  }
  if (a != aa) {       //If the value changes, the parameter changes. aa is an intermediate variable;
    aa = a;
  }
  if (b != bb) {
    bb = b;
  }
  if (c != cc) {

    cc = c;
  }
  if (d != dd) {

    dd = d;
  }
  if (e != ee) {

    ee = e;
  }
int x_1 = digitalRead(x);     //Read the level of the switch channel;

  if (x_1 == 0)
  {
    Mirf.send((byte *)&f);    //If the switch channel is low level, data will be sent; I connect a 1k pull-up resistor (connected to 5v) to the switch channel without interference;
    while (Mirf.isSending()) {
    }
  }
  int y_1 = digitalRead(y);
  //Serial.println(y_1);
  if (y_1 == 0)
  {
    Mirf.send((byte *)&g);
    while (Mirf.isSending()) {
    }
  }
  if (y_1 == 1)
  {
    Mirf.send((byte *)&i);
    while (Mirf.isSending()) {
    }
  }
  int z_1 = digitalRead(z);
  if (z_1 == 0)
  {
    Mirf.send((byte *)&h);
    while (Mirf.isSending()) {
    }
  }
//DEBUG: 
//Serial.print("LH STICK MOVEMENT UP/DOWN - ");
//Serial.println(a); //Midpoint = 494
//Serial.print("RH STICK MOVEMENT UP/DOWN - ");
//Serial.println(b);  //Centerpoint = 1459
//Serial.print("LH STICK MOVEMENT LEFT/RIGHT - ");
//Serial.println(c);
//Serial.print("RH STICK MOVEMENT LEFT/RIGHT - ");
//Serial.println(d);
  delay(10);                        // Wait for 0.01 seconds, wait for the receiving part to clear the cache;
}
