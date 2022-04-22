
//#include <SHT1x.h>
//
//// Specify data and clock connections and instantiate SHT1x object
//#define dataPin  10
//#define clockPin 11
//SHT1x sht1x(dataPin, clockPin);

#include <Adafruit_BMP085.h>
Adafruit_BMP085 bmp;

#include "LiquidCrystal.h"
const int rs=12,en=11,d4=5,d5=4,d6=3,d7=2;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

#define MQpin A0

#define flamePin A1

#define fan 8

#include <LM35.h>
LM35 temp(A2);

void setup()
{
   Serial.begin(9600); // Open serial connection to report values to host

   pinMode(MQpin, INPUT_PULLUP);

   pinMode(flamePin, INPUT_PULLUP);

   pinMode(fan, OUTPUT);
   
   if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
   while (1) {}
   }
   Serial.println("Starting up");

  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("CSE360");
  lcd.setCursor(0,1);
  lcd.print("Industrial Auto");
  delay(700);
  lcd.clear();
}

void loop()
{
  lcd.print("Pressure:");
  lcd.print(bmp.readPressure());
  lcd.print("Pa");
  
  lcd.setCursor(0,1);
  
  lcd.print("Temp: ");
  lcd.print(temp.cel());
  lcd.print(" C");
  
  delay(700);
  lcd.clear();
  Serial.println(" Pa");

  while (bmp.readPressure() > 100000 || digitalRead(MQpin) == HIGH || digitalRead(flamePin)==HIGH || temp.cel() > 30){
    if (digitalRead(MQpin) == HIGH) {
      lcd.print("Gas detected!!!");
      delay(1000);
      lcd.clear();
    }
    
    if (bmp.readPressure() > 100000){
      lcd.print("Lower the");
      lcd.setCursor(0,1);
      lcd.print("Pressure!!");
      delay(1000);
      lcd.clear();
    }

    if (digitalRead(flamePin) == HIGH){
      lcd.print("Flame detected!!!");
      delay(1000);
      lcd.clear();
    }

    if (temp.cel() > 30){
      digitalWrite(fan, HIGH);
      lcd.print("Fanning out the");
      lcd.setCursor(0,1);
      lcd.print("hot air!!!");
      delay(1000);
      lcd.clear();
    }
  }

  digitalWrite(fan, LOW);

}
