#include <Arduino.h>
#include <OneWire.h>
#include <DS18B20.h>
#include "liquidmixer.h"
#include "EEPROM.h"
#include "LCDIC2.h"
#include "Encoder.h"

DS18B20 ds(2);
LCDIC2 lcd(0x27,16,2);
uint8_t address[] = {40, 250, 31, 218, 4, 0, 0, 52};
uint8_t selected;
uint8_t minc = 38;
uint8_t maxc = 42;
bool instLCD = false;
Encoder myEnc(5,6) // Encoder lábak


void setup() {
  // put your setup code here, to run once:
  instLCD = lcd.begin();
  Serial.begin(115200);
  if (selected) {
    ds.setAlarms(minc, maxc);
  } else {
    if (instLCD) {
      lcd.print(NO_TEMP);
    } else {
      Serial.println(NO_TEMP);
    }
  }

}

void loop() {
  // put your main code here, to run repeatedly:
}