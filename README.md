# FwBox_UnifiedLcd
The library can detect LCD's IIC address automatically. Support the devices below.

![image](https://img.alicdn.com/imgextra/i4/13560478/O1CN011FOxlPglStaUqmX_!!13560478.jpg)
![image](https://gd1.alicdn.com/imgextra/i3/1804731589/O1CN01sl0oax1Nbo18iJsvt_!!1804731589.jpg)

# Required libries :
- https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
- https://github.com/fw-box/DFRobot_LCD

# Wiring for ESP8266:
| LCD1602 IIC | ESP8266 |
|-----|-----|
| VCC | 5V |
| GND | GND |
| SCL | GPIO05 (D1) |
| SDA | GPIO04 (D2) |
-----------

# Wiring for ESP32:
| LCD1602 IIC | ESP32 |
|-----|-----|
| VCC | 5V |
| GND | GND |
| SCL | GPIO22 |
| SDA | GPIO21 |
-----------

# Example
    #include "Wire.h"
    #include "FwBox_UnifiedLcd.h"

    FwBox_UnifiedLcd UnifiedLcd(16, 2);

    void setup() {
      Serial.begin(115200);
      Wire.begin(); // Join I2C bus
      UnifiedLcd.begin();
    }

    void loop() {
      UnifiedLcd.setCursor(0, 0);
      UnifiedLcd.print("   fw-box.com   ");
      UnifiedLcd.setCursor(0, 1);
      UnifiedLcd.print("  Hello World!  ");
      delay(2000);
    }

