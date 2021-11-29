#include <Arduino.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>

//버튼(앞문 0, 뒷문 2, led 1-3)
const int Button[4] = {2,4,5,3};
boolean lastButton[4] = {LOW,LOW,LOW,LOW};
boolean currentButton[4] = {LOW,LOW,LOW,LOW};

//led
const int F_LED = 9;
const int B_LED =  8;
boolean F_stateLED = false;
boolean B_stateLED = false;

//앞문
boolean F_doorState = 0;

//뒷문
SoftwareSerial mySerial(6, 7);
boolean B_doorState = false; 
byte c;
                                                                       
boolean debounce(boolean last, int pin);
byte transferAndWait(const byte what);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  SPI.begin();
  pinMode(SS,OUTPUT);
  pinMode(F_LED,OUTPUT);
  pinMode(B_LED,OUTPUT);
  digitalWrite(SS,HIGH);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  for(int i = 0; i<4; i++){
    pinMode(Button[i],INPUT);
  }
 
}

void loop() {
  for(int i = 0; i<4; i++){
  currentButton[i] = debounce(lastButton[i],Button[i]);
  }
  //SPI 통신
  byte F_door;
  digitalWrite(SS, LOW);
  if(currentButton[0] ==HIGH && lastButton[0]==LOW &&!F_doorState){
    F_doorState = true;
    const byte *p ='1';
    SPI.transfer(p);
  }
  else if (currentButton[0] == HIGH && lastButton[0] == LOW && F_doorState){
    F_doorState = false;
    const byte *p ='0';
    SPI.transfer(p);
  }
  lastButton[0] = currentButton[0];
  digitalWrite(SS, HIGH);
  //delay(1000);

  //뒷문
  if(currentButton[2] ==HIGH && lastButton[2]==LOW && !B_doorState){
    B_doorState = true;
    mySerial.write("open\n");
  }
  else if (currentButton[2] == HIGH && lastButton[2] == LOW && B_doorState){
    B_doorState = false;
    mySerial.write("close\n");
  }
  //lastButton[2] = currentButton[2];
  if(mySerial.available()){
      c = mySerial.read();
      if(c == '1'){
        B_doorState = true;
      }
    }
   lastButton[2] = currentButton[2];

  //led
  if(currentButton[1] == HIGH && lastButton[1] == LOW){
    F_stateLED = !F_stateLED;
  }
  lastButton[1] = currentButton[1];
  digitalWrite(F_LED,F_stateLED);
  if(currentButton[3] == HIGH && lastButton[3] == LOW){
    B_stateLED = !B_stateLED;
  }
  lastButton[3] = currentButton[3];
  digitalWrite(B_LED,B_stateLED);
}

boolean debounce(boolean last,int pin)
{
  boolean current = digitalRead(pin);
  if (current != last)
  {
    delay(5);
    current = digitalRead(pin);
  }
  return current;
}