#include <Arduino.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <String.h>
#include <Wire.h>

#define sv 8

SoftwareSerial mySerial(6, 7);

const int pinServo = 3;
const int pinTrig = 2;
const int pinEcho = 4;

const int RS = 8; const int EN = 9;
const int D4 = 10; const int D5 = 11;
const int D6 = 12; const int D7 = 13;

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// 서보모터
Servo servo;

// 초음파
int rangeMax = 200;
int rangeMin = 0;

long L;

boolean dooropen = false;
boolean openclose = false; // 문이 열렸다 닫힘?
boolean isClosed = false;

unsigned long l1, l2;

// 장애인 표시
byte creat1[] = {
  B00000,
  B00000,
  B00110,
  B01000,
  B10000,
  B10000,
  B01001,
  B00110
};

byte creat2[] = {
  B10000,
  B00000,
  B10000,
  B10000,
  B11000,
  B01000,
  B01100,
  B00000
};

void setup() {
    Serial.begin(9600);
    mySerial.begin(9600);

    Wire.begin(sv);
    Wire.onReceive(receiveEvent);

    pinMode(pinTrig, OUTPUT);
    pinMode(pinEcho, INPUT);

    // 서보모터
    servo.attach(pinServo);
    servo.write(180);

    Serial.println("S - start");

    // LCD
    lcd.begin(16, 2);
    lcd.createChar(1, creat1);
    lcd.createChar(2, creat2);
}

String strOpen = "open";
String strClose = "close";
byte c = "1";

void loop() {
    // 초음파
    digitalWrite(pinTrig, LOW); delayMicroseconds(2);
    digitalWrite(pinTrig, HIGH); delayMicroseconds(10);
    digitalWrite(pinTrig, LOW);

    L = pulseIn(pinEcho, HIGH) / 58.82;
    Serial.println(L);

    // 초음파부터 땅바닥까지 약 18cm
    // 초음파부터 문바닥(끝)까지 약 12cm

    // UART통신(M:버튼 - S:뒷문) 마스터 버튼을 누르면 뒷문이 열림
    if (mySerial.available()) {
        // Serial.readStringUntil('\n') \n문자를 만날때 까지 문자열 읽기
        String inString = mySerial.readStringUntil('\n');
        boolean open = inString.equals(strOpen);
        boolean close = inString.equals(strClose);
        if (open) {
            servo.write(0);
            Serial.println("S - open");
            //lcd.clear();
            //lcd.setCursor(0, 0); lcd.print("                ");
            //lcd.setCursor(5, 0); lcd.print("OPEN!");
            lcd.setCursor(0, 1); lcd.print("                ");
        }
        else if (close) {
            servo.write(180);
            openclose = true;

            l1 = millis();
            isClosed = true;
            Serial.println("S - close");
            //lcd.clear();
            //lcd.setCursor(0, 0); lcd.print("                ");
            //lcd.setCursor(5, 0); lcd.print("CLOSE");
            lcd.setCursor(0, 1); lcd.print("                ");
        }
    }

    // UART통신(M:버튼 - S:뒷문) 초음파로 인해 문열린 것 감지 > 마스터에 문열렀다고 알림
    if (isClosed && openclose && L <= 8) {
        servo.write(0);
        dooropen = true;
        openclose = false;
        Serial.println("S - 문끼임, open");
        lcd.setCursor(0, 1); lcd.print("                ");
        lcd.setCursor(1, 1); lcd.print("CHECK BACKDOOR");
        mySerial.write('1'); // 문끼임 발생하여 마스터쪽 close를 open으로 바꿈
    }

    l2 = millis();
    if (l2 - l1 >= 3000) {
        isClosed = false;
    }

}

// I2C통신(M:조이스틱 - S:뒷문 기사님 LCD) 버스 예약 후 버스 내부 LCD에 예약 출력
void receiveEvent(int howMany) {
    char c = Wire.read();

    switch (c) {
    case '1':
        lcd.setCursor(0, 0); lcd.print("                ");
        lcd.setCursor(5, 0); lcd.write(1);
        lcd.setCursor(6, 0); lcd.write(2);
        lcd.setCursor(8, 0); lcd.print("400");
        lcd.setCursor(0, 1); lcd.print("                ");
        //lcd.setCursor(0, 1); lcd.write(1); 
        //lcd.setCursor(1, 1); lcd.write(2);
        lcd.setCursor(1, 1); lcd.print("SCH University");
        break;

    case '2':
        lcd.setCursor(0, 0); lcd.print("                ");
        lcd.setCursor(5, 0); lcd.write(1);
        lcd.setCursor(6, 0); lcd.write(2);
        lcd.setCursor(8, 0); lcd.print("403");
        //lcd.setCursor(0, 1); lcd.write(1); 
        //lcd.setCursor(1, 1); lcd.write(2);
        lcd.setCursor(1, 1); lcd.print("SCH University");
        break;

    case '3':
        lcd.setCursor(0, 0); lcd.print("                ");
        lcd.setCursor(5, 0); lcd.write(1);
        lcd.setCursor(6, 0); lcd.write(2);
        lcd.setCursor(8, 0); lcd.print("410");
        //lcd.setCursor(0, 1); lcd.write(1); 
        //lcd.setCursor(1, 1); lcd.write(2);
        lcd.setCursor(1, 1); lcd.print("SCH University");
        break;

    case '4':
        lcd.setCursor(0, 0); lcd.print("                ");
        lcd.setCursor(5, 0); lcd.write(1);
        lcd.setCursor(6, 0); lcd.write(2);
        lcd.setCursor(8, 0); lcd.print("430");
        //lcd.setCursor(0, 1); lcd.write(1); 
        //lcd.setCursor(1, 1); lcd.write(2);
        lcd.setCursor(1, 1); lcd.print("SCH University");
        break;

    case '5':
        lcd.setCursor(0, 0); lcd.print("                ");
        lcd.setCursor(5, 0); lcd.write(1);
        lcd.setCursor(6, 0); lcd.write(2);
        lcd.setCursor(8, 0); lcd.print("441");
        //lcd.setCursor(0, 1); lcd.write(1); 
        //lcd.setCursor(1, 1); lcd.write(2);
        lcd.setCursor(1, 1); lcd.print("SCH University");
        break;
    }
}
