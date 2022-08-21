#ifndef __DEVICE_MODE_RUNNING_H__
#define __DEVICE_MODE_RUNNING_H__

#include "device_mode.h"
#include <Arduino.h>
#include <freertos/event_groups.h>

extern EventGroupHandle_t meterEventGroup;
extern EventGroupHandle_t ledEventGroup;

class DeviceModeRunning : public DeviceMode
{
private:
    LCD_ST7032 *lcd;
    double litersTarget = 0.0;
    double litersCount = 0.0;
    uint8_t isPauzed = false;
    std::function<void(void)> *onExitCallback = nullptr;

public:
    DeviceModeRunning(LCD_ST7032 *lcd, double litersTarget, std::function<void(void)>* onExit);
    ~DeviceModeRunning();

    void initialise();
    void rotatedClockwise(void);
    void rotatedCounterClockwise(void);
    void pressed(void);
    void setLiters(double liters);
};

#endif