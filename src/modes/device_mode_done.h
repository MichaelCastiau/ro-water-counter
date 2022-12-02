#ifndef __DEVICE_MODE_DONE_H__
#define __DEVICE_MODE_DONE_H__

#include "device_mode.h"
#include <Arduino.h>
#include <freertos/event_groups.h>

extern EventGroupHandle_t ledEventGroup;
extern EventGroupHandle_t meterEventGroup;
extern QueueHandle_t doneLitersQueue;

class DeviceModeDone : public DeviceMode
{
private:
    LCD_ST7032 *lcd;
    double litersFilled = 0.0;
    std::function<void(void)> *onResetCallback = nullptr;

public:
    DeviceModeDone(LCD_ST7032 *lcd, double litersFilled, std::function<void(void)> *resetCallback);
    ~DeviceModeDone();

    void initialise();
    void rotatedClockwise(void);
    void rotatedCounterClockwise(void);
    void setLiters(double liters);
    void pressed(void);
    void pressedLong(void);
    void tick();
};

#endif