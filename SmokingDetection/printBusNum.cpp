#include "printBusNum.h"

LiquidCrystal_I2C lcd(0x27,20,4);

uint8_t c[]{
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F
};

uint8_t b[] = {
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00
};

uint8_t up[] = {
  0x00,
  0x00,
  0x00,
  0x00,
  0x1F,
  0x1F,
  0x1F,
  0x1F
};

uint8_t down[] = {
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x00,
  0x00,
  0x00,
  0x00
};

uint8_t head[] = {
  0x00,
  0x00,
  0x1E,
  0x1E,
  0x1E,
  0x1E,
  0x00,
  0x00
};

uint8_t back[] = {
  0x1E,
  0x1E,
  0x1E,
  0x1E,
  0x00,
  0x00,
  0x00,
  0x00
};

uint8_t body[] = {
  0x1E,
  0x1E,
  0x1E,
  0x1E,
  0x1E,
  0x1E,
  0x1E,
  0x1E
};

uint8_t leg[] = {
  0x1C,
  0x1C,
  0x1C,
  0x1C,
  0x1C,
  0x1C,
  0x1C,
  0x1C
};

void callLCD() {
    lcd.begin(16, 2);
    lcd.init();
    lcd.backlight();
}

void myCreatChar(){
    lcd.createChar(0, c);
    lcd.createChar(1, b);
    lcd.createChar(2, up);
    lcd.createChar(3, down);
    lcd.createChar(4, head);
    lcd.createChar(5, back);
    lcd.createChar(6, body);
    lcd.createChar(7, leg);
}

void printIcon(int i, int j){
    lcd.setCursor(i, j);
    lcd.write(1);
    lcd.write(1);
    lcd.write(4);
    lcd.write(1);
    lcd.write(1);

    lcd.setCursor(i, j+1);
    lcd.write(2);
    lcd.write(5);
    lcd.write(6);
    lcd.write(1);
    lcd.write(1);

    lcd.setCursor(i, j+2);
    lcd.write(0);
    lcd.write(1);
    lcd.write(3);
    lcd.write(7);
    lcd.write(1);

    lcd.setCursor(i, j+3);
    lcd.write(1);
    lcd.write(3);
    lcd.write(5);
    lcd.write(5);
    lcd.write(1);
}

void print0(int i, int j){
    lcd.setCursor(i, j);
    lcd.write(0);
    lcd.write(0);
    lcd.write(0);

    lcd.setCursor(i, j+1);
    lcd.write(0);
    lcd.write(1);
    lcd.write(0);

    lcd.setCursor(i, j+2);
    lcd.write(0);
    lcd.write(1);
    lcd.write(0);

    lcd.setCursor(i, j+3);
    lcd.write(0);
    lcd.write(0);
    lcd.write(0);
}

void print1(int i, int j){
    lcd.setCursor(i, j);
    lcd.write(0);
    lcd.write(0);
    lcd.write(1);

    lcd.setCursor(i, j+1);
    lcd.write(1);
    lcd.write(0);
    lcd.write(1);

    lcd.setCursor(i, j+2);
    lcd.write(1);
    lcd.write(0);
    lcd.write(1);

    lcd.setCursor(i, j+3);
    lcd.write(0);
    lcd.write(0);
    lcd.write(0);
}

void print3(int i, int j){
    lcd.setCursor(i, j);
    lcd.write(0);
    lcd.write(0);
    lcd.write(0);

    lcd.setCursor(i, j+1);
    lcd.write(2);
    lcd.write(2);
    lcd.write(0);

    lcd.setCursor(i, j+2);
    lcd.write(3);
    lcd.write(3);
    lcd.write(0);

    lcd.setCursor(i, j+3);
    lcd.write(0);
    lcd.write(0);
    lcd.write(0);
}
void print4(int i, int j){
    lcd.setCursor(i, j);
    lcd.write(0);
    lcd.write(1);
    lcd.write(0);

    lcd.setCursor(i, j+1);
    lcd.write(0);
    lcd.write(0);
    lcd.write(0);

    lcd.setCursor(i, j+2);
    lcd.write(1);
    lcd.write(1);
    lcd.write(0);

    lcd.setCursor(i, j+3);
    lcd.write(1);
    lcd.write(1);
    lcd.write(0);
}