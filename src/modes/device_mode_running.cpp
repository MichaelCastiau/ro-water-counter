#include "device_mode_running.h"

DeviceModeRunning::DeviceModeRunning(LCD_ST7032 *lcd, double litersTarget)
{
    this->lcd = lcd;
    this->litersTarget = litersTarget;
}
DeviceModeRunning::~DeviceModeRunning() {}
void DeviceModeRunning::initialise()
{
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("System running");
    lcd->setCursor(1, 0);

    uint64_t numberLitersTarget = ((uint64_t)litersTarget * 10) / 10;
    uint64_t decimalsLitersTarget = (litersTarget - (double)numberLitersTarget) * 10;

    lcd->print("0.0 /");
    lcd->print(numberLitersTarget, DEC);
    lcd->print(".");
    lcd->print(decimalsLitersTarget, DEC);

    lcd->setCursor(1, 10); // Liters appears at the end of the screen
    lcd->print("Liters");

    digitalWrite(LED_NORMAL, LOW);
    digitalWrite(LED_ERROR, HIGH);
}
void DeviceModeRunning::rotatedClockwise(void)
{
}
void DeviceModeRunning::rotatedCounterClockwise(void)
{
}
void DeviceModeRunning::pressed(void)
{
    isPauzed = !isPauzed;
    lcd->setCursor(0, 0);
    if (isPauzed)
        lcd->print("System pauzed   ");
    else
        lcd->print("System running  ");
}

void DeviceModeRunning::onPressed(std::function<void(double)> callback)
{
    this->onPressedCallback = &callback;
}