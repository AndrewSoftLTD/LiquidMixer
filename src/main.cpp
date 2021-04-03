#include <Arduino.h>
#include <OneWire.h>
#include "DS18B20.h"
#include "liquidmixer.h"
#include "EEPROM.h"

OneWire sens(10);
//DS18B20 sensor(&sens);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
}