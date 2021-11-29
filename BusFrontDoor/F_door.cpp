#include <Arduino.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <Servo.h>

SoftwareSerial mySoftwareSerial(5, 6);
DFRobotDFPlayerMini myDFPlayer;
Servo servo;

const int pinServo = 3;

void printDetail(uint8_t type, int value);

char buf;
volatile boolean done = false;

void setup()
{
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);

  servo.attach(pinServo);
  servo.write(0);

  pinMode(MISO,OUTPUT);
  SPCR |= _BV(SPE);
  SPCR |= _BV(SPIE);
  SPCR &= ~_BV(MSTR);
  if (!myDFPlayer.begin(mySoftwareSerial))
  {
    Serial.println(F("DF Player 오류"));
    while (true)
    {
      delay(0);
    }
  }
  myDFPlayer.volume(30);
}

ISR(SPI_STC_vect){
  byte c = SPDR;
  buf = c;
  done = true;
}

void loop()
{
  if(done){
    Serial.print(buf);
    if(buf == '1'){
      servo.write(180);
      myDFPlayer.play(1);
    }
    else if(buf == '0'){
      servo.write(0);
    }
     done = false;
  }
}