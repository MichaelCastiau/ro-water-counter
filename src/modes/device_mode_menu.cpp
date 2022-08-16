#include "device_mode_menu.h"

DeviceModeMenu::DeviceModeMenu(LCD_ST7032 *lcd)
{
    this->lcd = lcd;
}
DeviceModeMenu::~DeviceModeMenu() {}
void DeviceModeMenu::initialise()
{
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("RO Water Counter");
    lcd->setCursor(1, 0);
    lcd->print("0.0");
    lcd->setCursor(1, 3);
    lcd->print("Liters");
}
void DeviceModeMenu::rotatedClockwise(void)
{
    if (liters < 50)
    {
        liters += 0.1;
        lcd->setCursor(1, 0);
        lcd->print(((uint8_t)liters * 10) / 10, DEC);
        lcd->print(".");
        lcd->print(((uint8_t)liters * 10) % 10, DEC);
    }
}
void DeviceModeMenu::rotatedCounterClockwise(void)
{
    if (liters > 0.2)
    {
        liters -= 0.1;
        lcd->setCursor(1, 0);
        lcd->print(((uint8_t)liters * 10) / 10, DEC);
        lcd->print(".");
        lcd->print(((uint8_t)liters * 10) % 10, DEC);
    }
}
void DeviceModeMenu::pressed(void)
{
    if (this->onPressedCallback)
    {
        return (*this->onPressedCallback)(this->liters);
    }
}

void DeviceModeMenu::onPressed(std::function<void(double)> callback)
{
    this->onPressedCallback = &callback;
}