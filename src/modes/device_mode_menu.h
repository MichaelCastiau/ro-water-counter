#ifndef __DEVICE_MODE_MENU_H__
#define __DEVICE_MODE_MENU_H__

#include "device_mode.h"
#include <Arduino.h>
#include <freertos/event_groups.h>


extern EventGroupHandle_t ledEventGroup;

class DeviceModeMenu : public DeviceMode
{
private:
    LCD_ST7032 *lcd;
    double liters = 0.0;
    std::function<void(double)>* startCallback = nullptr;
public:
    DeviceModeMenu(LCD_ST7032 *lcd, std::function<void(double)>* startCallback);
    ~DeviceModeMenu();

    void initialise();
    void rotatedClockwise(void);
    void rotatedCounterClockwise(void);
    virtual void setLiters(double liters);
    void pressed(void);
};

#endif