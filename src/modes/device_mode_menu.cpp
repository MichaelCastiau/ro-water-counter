#include "device_mode_menu.h"

DeviceModeMenu::DeviceModeMenu(LCD_ST7032 *lcd, std::function<void(double)> *startCallback)
{
    this->lcd = lcd;
    this->startCallback = startCallback;
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

    xEventGroupClearBits(ledEventGroup, 0xff);
    xEventGroupSetBits(ledEventGroup, LED_STATE_IDLE);
    xEventGroupSetBits(meterEventGroup, RESET_FLOW_METER);

    digitalWrite(PIN_RELAY_OUT, LOW);
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
    if (liters > 0.5)
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
    return (*this->startCallback)(this->liters);
}
void DeviceModeMenu::setLiters(double liters) {}
void DeviceModeMenu::pressedLong()
{
}