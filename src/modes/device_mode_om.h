#ifndef __DEVICE_MODE_OPERATION_MODE_H__
#define __DEVICE_MODE_OPERATION_MODE_H__

#include "device_mode.h"
#include <LCD_ST7032.h>
#include <functional>

enum DeviceModeEnum
{
    COUNTER,
    ATO
};

class DeviceModeOperationMode : public DeviceMode
{
private:
    LCD_ST7032 *lcd;
    DeviceModeEnum mode = COUNTER;
    std::function<void(void)> *onStartCounter;
    std::function<void(void)> *onStartATO;

public:
    DeviceModeOperationMode(LCD_ST7032 *lcd, std::function<void(void)> *startCounter, std::function<void(void)> *startATO);
    ~DeviceModeOperationMode();
    void initialise();
    void rotatedClockwise(void);
    void rotatedCounterClockwise(void);
    void pressed(void);
    void pressedLong(void);
    void setLiters(double liters);
    void tick();
};

#endif