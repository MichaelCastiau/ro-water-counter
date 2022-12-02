#ifndef __DEVICE_MODE_ATO_H__
#define __DEVICE_MODE_ATO_H__

#include "device_mode.h"
#include <LCD_ST7032.h>

extern EventGroupHandle_t levelEventGroup;

class DeviceModeATO : public DeviceMode
{
    LCD_ST7032 *lcd;

public:
    DeviceModeATO(LCD_ST7032 *lcd);
    ~DeviceModeATO();
    void initialise();
    void rotatedClockwise(void);
    void rotatedCounterClockwise(void);
    void pressed(void);
    void pressedLong(void);
    void setLiters(double liters);
    void tick();

private:
    void normalLevel();
};

#endif