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


#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <Wire.h>

#include "FwBox_UnifiedLcd.h"


FwBox_UnifiedLcd::FwBox_UnifiedLcd(uint8_t lcd_cols, uint8_t lcd_rows)
{
    FwBox_UnifiedLcd::LcdLibType = 0;
    FwBox_UnifiedLcd::Col = lcd_cols;
    FwBox_UnifiedLcd::Row = lcd_rows;
}

int FwBox_UnifiedLcd::begin()
{
    int iic_addr = 0;

    Wire.begin();

    //
    // Scan the IIC address.
    //
    Wire.beginTransmission((0x7c>>1)); // Address - (0x7c>>1) is DFRobot LCD's.
    uint8_t data8 = Wire.endTransmission();
    if (data8 == 0) {
        FwBox_UnifiedLcd::LcdLibType = LCD_LIB_TYPE_DFROBOT;
        FwBox_UnifiedLcd::Col = 16;
        FwBox_UnifiedLcd::Row = 2;
        iic_addr = (0x7c>>1);
    }
    else {
        //
        // Scan Lcd IIC address in table - TryLcdAddress.
        //
        for(int i = 0; i < (sizeof(TryLcdAddress) / sizeof(int)); i++) {
            Wire.beginTransmission(TryLcdAddress[i]);
            data8 = Wire.endTransmission();
            if (data8 == 0) {
                FwBox_UnifiedLcd::LcdLibType = LCD_LIB_TYPE_COMMON;
                iic_addr = TryLcdAddress[i];
                break;
            }
        }
    }
    
    if(FwBox_UnifiedLcd::LcdLibType == 0) {
        return 1; // Error
    }

    //
    // Create the LCD instance and init it.
    //
    if(LcdLibType == LCD_LIB_TYPE_DFROBOT) {
        DfrobotLcd = new DFRobot_LCD(16, 2);
        if(DfrobotLcd != 0) {
            DfrobotLcd->init();
            //delay(100);
            DfrobotLcd->display();
            return 0; // Success
        }
    }
    else if(LcdLibType == LCD_LIB_TYPE_COMMON) {
        CommonLcd = new LiquidCrystal_I2C(iic_addr, FwBox_UnifiedLcd::Col, FwBox_UnifiedLcd::Row);
        if(CommonLcd != 0) {
            CommonLcd->begin();
            CommonLcd->backlight();
            return 0; // Success
        }
    }
    
    return 1; // Error
}

inline size_t FwBox_UnifiedLcd::write(uint8_t value) {
    if(LcdLibType == LCD_LIB_TYPE_DFROBOT) {
        if(DfrobotLcd != 0) {
            DfrobotLcd->write(value);
        }
    }
    else if(LcdLibType == LCD_LIB_TYPE_COMMON) {
        if(CommonLcd != 0) {
            CommonLcd->write(value);
        }
    }
	return 1;
}

void FwBox_UnifiedLcd::setCursor(uint8_t col, uint8_t row)
{
    if(LcdLibType == LCD_LIB_TYPE_DFROBOT) {
        if(DfrobotLcd != 0) {
            DfrobotLcd->setCursor(col, row);
        }
    }
    else if(LcdLibType == LCD_LIB_TYPE_COMMON) {
        if(CommonLcd != 0) {
            CommonLcd->setCursor(col, row);
        }
    }
}

void FwBox_UnifiedLcd::setRGB(uint8_t r, uint8_t g, uint8_t b)
{
    if(LcdLibType == LCD_LIB_TYPE_DFROBOT) {
        if(DfrobotLcd != 0) {
            DfrobotLcd->setRGB(r, g, b);
        }
    }
}

void FwBox_UnifiedLcd::printAtCenter(int y, char* str)
{
    //
    // Center the string.
    //
    int space_count = (FwBox_UnifiedLcd::Col - strlen(str)) / 2;
    setCursor(0, y);
    for(int i = 0; i < space_count; i++)
        print(" ");

    print(str);

    space_count = 16 - space_count - strlen(str);

    for(int i = 0; i < space_count; i++)
        print(" ");
}

/*
void FwBox_UnifiedLcd::printSpace(int count)
{
    char* str = new char[FwBox_UnifiedLcd::Col + 1];
    int new_count = count;
    
    if(count > FwBox_UnifiedLcd::Col)
        new_count = FwBox_UnifiedLcd::Col;

    memset(&(str[0]), ' ', new_count);
    str[new_count] = '\0';

    if(LcdLibType == LCD_LIB_TYPE_DFROBOT) {
        if(DfrobotLcd != 0) {
            DfrobotLcd->print(str);
        }
    }
    else if(LcdLibType == LCD_LIB_TYPE_COMMON) {
        if(CommonLcd != 0) {
            CommonLcd->print(str);
        }
    }

    delete [] str;
}
*/
