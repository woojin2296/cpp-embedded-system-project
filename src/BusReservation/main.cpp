#include <Arduino.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <SPI.h>
#include <Wire.h>

#define sv 8

bool isPeopleExist();
void startReservation();

SoftwareSerial DFPlayerSerial(6, 7);
DFRobotDFPlayerMini DFPlayer;

const int pinJOY_PUSH = 8;
const int pinJOY_X = A0;
const int pinJOY_Y = A1;
const int pinPIR = 9;

void setup() {
  Serial.begin(9600);
  DFPlayerSerial.begin(9600);

  Wire.begin();
  SPI.begin(); 

  pinMode(pinJOY_PUSH, INPUT_PULLUP);
  pinMode(SS,OUTPUT);

  if (!DFPlayer.begin(DFPlayerSerial)) { 
    Serial.println(F("DF Player 오류"));
    while(true) { delay(0); }
  }
  
  DFPlayer.volume(50);

  digitalWrite(SS,HIGH); 
  SPI.setClockDivider(SPI_CLOCK_DIV16);
}

void loop() {
  digitalWrite(SS, LOW);

  if (isPeopleExist()) startReservation();
  delay(100);
}

bool isPeopleExist() {
  Serial.println(digitalRead(pinPIR));

  if (digitalRead(pinPIR)) {
    DFPlayer.play(7);
    while (true) {
      if (!(digitalRead(pinJOY_PUSH))) { return true; }
      delay(100);
    }
  }

  return false;
}

void startReservation(){
  DFPlayer.play(8);
  delay(2000);

  int index = 0;
  bool secondZero = false;
  bool output = false;
  bool onReservation = false;

  while(1) {
    if (analogRead(pinJOY_X) == 1023 && !onReservation){
      index++;
      secondZero = true;
      if (index >= 6) index = 1;
      output = false;
    } 

    if (analogRead(pinJOY_X) == 0 && !onReservation){
      index--;
      if (index < 0 && !secondZero) {
        index = 5;
        secondZero = true;
      }
      if (index <= 0 && secondZero) index = 5;
      output = false;
    }

    switch (index) {
      case 0:
        break;
      case 1:
        if (!output) {
          DFPlayer.play(1);
          output = true;
          delay(1500);
        }
        break;
      case 2:
        if (!output) {
          DFPlayer.play(2);
          output = true;
          delay(1500);
        }
        break;
      case 3:
        if (!output) {
          DFPlayer.play(3);
          output = true;
          delay(1500);
        }
        break;
      case 4:
        if (!output) {
          DFPlayer.play(4);
          output = true;
          delay(1500);
        }
        break;     
      case 5:
        if (!output) {
          DFPlayer.play(5);
          output = true;
          delay(1500);
        }
        break;
    }

    if (index >= 1 && index <= 5 && analogRead(pinJOY_Y) == 1023){
      if (onReservation){
        DFPlayer.play(6);

        switch (index) {
          case 1:
            SPI.transfer('1');
            break;
          case 2:
            SPI.transfer('2');
            break;
          case 3:
            SPI.transfer('3');
            break;
          case 4:
            SPI.transfer('4');
            break;
          case 5:
            SPI.transfer('5');
            break;      
        }

        Wire.beginTransmission(sv);

        switch (index) {
          case 1:
            Wire.write('1');
            break;
          case 2:
            Wire.write('2');
            break;
          case 3:
            Wire.write('3');
            break;
          case 4:
            Wire.write('4');
            break;
          case 5:
            Wire.write('5');
            break;      
        }     

        Wire.endTransmission();
 
        delay(2000);
        onReservation = false;
        return;
      }

      else {
        DFPlayer.play(9);
        delay(2000);
        onReservation = true;
      }
    }

    if (index >= 1 && index <= 5 && analogRead(pinJOY_Y) == 0 && onReservation){
      DFPlayer.play(10);
      delay(2000);
      onReservation = false;
    }

    delay(100);
  }
}