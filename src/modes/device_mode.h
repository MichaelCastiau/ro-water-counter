#ifndef __DEVICE_MODE_H__
#define __DEVICE_MODE_H__

#include <functional>
#include "LCD_ST7032.h"
#include "../config.h"

class DeviceMode
{
public:
    virtual void initialise() = 0;
    virtual void rotatedClockwise(void) = 0;
    virtual void rotatedCounterClockwise(void) = 0;
    virtual void pressed(void) = 0;
    virtual void pressedLong(void) = 0;
    virtual void setLiters(double liters) = 0;
    virtual void tick() = 0;
};

#endif