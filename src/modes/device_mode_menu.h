#ifndef __DEVICE_MODE_MENU_H__
#define __DEVICE_MODE_MENU_H__

#include "device_mode.h"

class DeviceModeMenu : public DeviceMode
{
private:
    LCD_ST7032 *lcd;
    double liters = 0.0;
    std::function<void(double)>* onPressedCallback = nullptr;
public:
    DeviceModeMenu(LCD_ST7032 *lcd);
    ~DeviceModeMenu();

    void initialise();
    void rotatedClockwise(void);
    void rotatedCounterClockwise(void);
    void pressed(void);

    void onPressed(std::function<void(double)> callback);
};

#endif