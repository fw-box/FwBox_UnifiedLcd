//
// Copyright (c) 2020 Fw-Box (https://fw-box.com)
// Author: Hartman Hsieh
//
// Description :
//   IIC address detects automatically.
//
// Connections :
//   LCD Module => IIC
//
// Required Library :
//   https://github.com/bearwaterfall/DFRobot_LCD-master
//   https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
//

#ifndef __FWBOX_UNIFIEDLCD_H__
#define __FWBOX_UNIFIEDLCD_H__

#include <inttypes.h>
#include "Print.h"


#define LCD_LIB_TYPE_DFROBOT 1
#define LCD_LIB_TYPE_COMMON 2


#include "DFRobot_LCD.h"
#include <LiquidCrystal_I2C.h>

class FwBox_UnifiedLcd : public Print 
{

public:
    FwBox_UnifiedLcd(uint8_t lcd_cols, uint8_t lcd_rows);

    //
    // return :
    //          0 - Success
    //          1 - Failed
    //
    int begin();

    virtual size_t write(uint8_t);
    void setCursor(uint8_t, uint8_t);
    void setRGB(uint8_t r, uint8_t g, uint8_t b); // Set backlight color
    void printAtCenter(int y, char* str);
    //void printSpace(int count);

private:
    int Col = 16;
    int Row = 2;
    DFRobot_LCD* DfrobotLcd = 0;
    LiquidCrystal_I2C* CommonLcd = 0;
    int LcdLibType = 0;
    int TryLcdAddress[2] = {0x27, 0x3f};

};

#endif // __FWBOX_UNIFIEDLCD_H__
