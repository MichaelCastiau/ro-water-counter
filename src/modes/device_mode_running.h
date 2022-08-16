#ifndef __DEVICE_MODE_RUNNING_H__
#define __DEVICE_MODE_RUNNING_H__

#include "device_mode.h"

class DeviceModeRunning : public DeviceMode
{
private:
    LCD_ST7032 *lcd;
    double litersTarget = 0.0;
    double litersCount = 0.0;
    std::function<void(double)>* onPressedCallback = nullptr;
    uint8_t isPauzed = false;
public:
    DeviceModeRunning(LCD_ST7032 *lcd, double litersTarget);
    ~DeviceModeRunning();

    void initialise();
    void rotatedClockwise(void);
    void rotatedCounterClockwise(void);
    void pressed(void);

    void onPressed(std::function<void(double)> callback);
};

#endif