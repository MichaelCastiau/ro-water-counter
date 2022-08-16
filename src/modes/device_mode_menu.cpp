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
    lcd->setCursor(1, 10); // Liters appears at the end of the screen
    lcd->print("Liters");
}
void DeviceModeMenu::rotatedClockwise(void)
{
    if (liters < 50)
    {
        liters += RE_STEPS;
        uint64_t number = ((uint64_t)liters * 10) / 10;
        uint64_t decimals = (liters - (double)number) * 10;

        lcd->setCursor(1, 0);
        lcd->print(number, DEC);
        lcd->print(".");
        lcd->print(decimals, DEC);
    }
}
void DeviceModeMenu::rotatedCounterClockwise(void)
{
    if (liters > 0.2)
    {
        liters -= RE_STEPS;
        uint64_t number = ((uint64_t)liters * 10) / 10;
        uint64_t decimals = (liters - (double)number) * 10;

        lcd->setCursor(1, 0);
        lcd->print(number, DEC);
        lcd->print(".");
        lcd->print(decimals, DEC);
    }
}
void DeviceModeMenu::pressed(void)
{
    return (*this->onPressedCallback)(this->liters);
}

void DeviceModeMenu::onPressed(std::function<void(double)> callback)
{
    this->onPressedCallback = &callback;
}