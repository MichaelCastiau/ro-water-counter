#include "device_mode_ato.h"

DeviceModeATO::DeviceModeATO(LCD_ST7032 *lcd)
{
    this->lcd = lcd;
}
DeviceModeATO::~DeviceModeATO() {}
void DeviceModeATO::initialise()
{
    normalLevel();
}
void DeviceModeATO::rotatedClockwise(void) {}
void DeviceModeATO::rotatedCounterClockwise(void) {}
void DeviceModeATO::pressed(void)
{
    // TODO show how much topped of since start
}
void DeviceModeATO::pressedLong(void) {}
void DeviceModeATO::tick(void)
{
    if (!(xEventGroupGetBits(levelEventGroup) & WATER_TOPPED_OFF))
    {
        lcd->setCursor(1, 0);
        lcd->print("Topping off...");
        digitalWrite(PIN_RELAY_OUT, HIGH);

        xEventGroupWaitBits(levelEventGroup, WATER_TOPPED_OFF, pdFALSE, pdFALSE, pdMS_TO_TICKS(10000));

        digitalWrite(PIN_RELAY_OUT, LOW);

        normalLevel();
    }
}
void DeviceModeATO::setLiters(double liters) {}
void DeviceModeATO::normalLevel()
{
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("ATO Mode");
    lcd->setCursor(1, 0);
    lcd->print("Level Normal");
}