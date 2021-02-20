//
// Copyright (c) 2020 Fw-Box (https://fw-box.com)
// Author: Hartman Hsieh
//
// Description :
//   None
//
// Connections :
//
// Required Library :
//   https://github.com/bearwaterfall/DFRobot_LCD-master
//   https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
//

//#include <ESP8266WiFi.h>
#include "Wire.h"
#include "FwBox_UnifiedLcd.h"

FwBox_UnifiedLcd UnifiedLcd(16, 2);

void setup() {
  Serial.begin(9600);
  Wire.begin(); // Join I2C bus
  UnifiedLcd.init();
}

void loop() {
  UnifiedLcd.setCursor(0, 0);
  UnifiedLcd.print("   fw-box.com   ");
  UnifiedLcd.setCursor(0, 1);
  UnifiedLcd.print("  Hello World!  ");
  delay(2000);
}
