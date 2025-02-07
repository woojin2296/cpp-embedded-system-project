#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif


void printIcon(int i, int j);
void print0(int i, int j);
void print1(int i, int j);
void print3(int i, int j);
void print4(int i, int j);
void myCreatChar();
void callLCD();
