#include <Arduino.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include "printBusNum.h"

SoftwareSerial DFPlayerSerial(6, 7);
DFRobotDFPlayerMini DFPlayer;

const int gasPin = A0;

bool playSound = true;
unsigned long l1, l2;

bool bus[] = {false, false, false, false, false};



void setup() {
  DFPlayerSerial.begin(9600);
  Serial.begin(9600);

  callLCD();

  myCreatChar();

  if (!DFPlayer.begin(DFPlayerSerial)) {
    Serial.println(F("DF Player 오류"));
    while(true){
      delay(0);
    }
  }
  DFPlayer.volume(50);

  SPCR |= _BV(SPE);
  SPCR |= _BV(SPIE);
  SPCR &= ~_BV(MSTR);
}

void loop() {
  Serial.println(analogRead(gasPin));

  if (analogRead(gasPin) >= 300 && playSound){
    DFPlayer.play(1);
    l1 = millis();
    playSound = false;
  }

  l2 = millis();
  if (l2 - l1 >= 5000) playSound = true;

  if (bus[0]) {
    printIcon(1, 0);
    print4(7, 0);
    print0(11, 0);
    print0(15, 0);
    bus[0] = false;
  }
  else if (bus[1]) {
    printIcon(1, 0);
    print4(7, 0);
    print0(11, 0);
    print3(15, 0);
    bus[1] = false;
  }
  else if (bus[2]) {
    printIcon(1, 0);
    print4(7, 0);
    print1(11, 0);
    print0(15, 0);
    bus[2] = false;
  }
  else if (bus[3]) {
    printIcon(1, 0);
    print4(7, 0);
    print3(11, 0);
    print0(15, 0);
    bus[3] = false;
  }
  else if (bus[4]) {
    printIcon(1, 0);
    print4(7, 0);
    print4(11, 0);
    print1(15, 0);
    bus[4] = false;
  }
  
  delay(100);
}

ISR(SPI_STC_vect) {
  byte c = SPDR;
  switch (c) {
    case '1':
      bus[0] = true;
      Serial.println("400");
      break;
    case '2':
      bus[1] = true;
      Serial.println("403");
      break;
    case '3':
      bus[2] = true;
      Serial.println("410");
      break;
    case '4':
      bus[3] = true;
      Serial.println("430");
      break;
    case '5':
      bus[4] = true;
      Serial.println("441");
      break;
  }
}