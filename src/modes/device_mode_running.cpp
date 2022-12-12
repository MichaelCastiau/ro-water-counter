#include "device_mode_running.h"

DeviceModeRunning::DeviceModeRunning(
    LCD_ST7032 *lcd,
    double litersTarget,
    std::function<void(void)> *onExit,
    std::function<void(double)> *onDone)
{
    this->lcd = lcd;
    this->litersTarget = litersTarget;
    this->onExitCallback = onExit;
    this->onDoneCallback = onDone;
}
DeviceModeRunning::~DeviceModeRunning() {}
void DeviceModeRunning::initialise()
{
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("System running");
    lcd->setCursor(1, 0);

    WSMessage message = {.startTime = 1L}; // passing 1 here will result in passing the time from the internet in the wifi task
    xQueueSend(toWSQueue, (void *)&message, pdMS_TO_TICKS(50));

    uint64_t numberLitersTarget = ((uint64_t)litersTarget * 10) / 10;
    uint64_t decimalsLitersTarget = (litersTarget - (double)numberLitersTarget) * 10;

    lcd->print("0.0 /");
    lcd->print(numberLitersTarget, DEC);
    lcd->print(".");
    lcd->print(decimalsLitersTarget, DEC);

    lcd->setCursor(1, 10); // Liters appears at the end of the screen
    lcd->print("Liters");
    digitalWrite(PIN_RELAY_OUT, HIGH);

    xEventGroupSetBits(meterEventGroup, RESET_FLOW_METER);

    xEventGroupClearBits(ledEventGroup, 0xff);
    xEventGroupSetBits(ledEventGroup, LED_STATE_NORMAL_RUNNIN);
}
void DeviceModeRunning::rotatedClockwise(void)
{
    if (litersTarget < 50 && isPauzed)
    {
        litersTarget += RE_STEPS;
        uint64_t number = ((uint64_t)litersTarget * 10) / 10;
        uint64_t decimals = (litersTarget - (double)number) * 10;

        lcd->setCursor(1, 5);
        lcd->print(number, DEC);
        lcd->print(".");
        lcd->print(decimals, DEC);

        this->setLiters(this->litersCount); // Recheck if we have met target
    }
}
void DeviceModeRunning::rotatedCounterClockwise(void)
{
    if (litersTarget > 0.5 && isPauzed)
    {
        litersTarget -= RE_STEPS;
        uint64_t number = ((uint64_t)litersTarget * 10) / 10;
        uint64_t decimals = (litersTarget - (double)number) * 10;

        lcd->setCursor(1, 5);
        lcd->print(number, DEC);
        lcd->print(".");
        lcd->print(decimals, DEC);

        this->setLiters(this->litersCount); // Recheck if we have met target
    }
}
void DeviceModeRunning::pressed(void)
{
    isPauzed = !isPauzed;
    lcd->setCursor(0, 0);
    if (isPauzed)
    {
        digitalWrite(PIN_RELAY_OUT, LOW);
        lcd->print("System pauzed   ");
        xEventGroupClearBits(ledEventGroup, 0xff);
        xEventGroupSetBits(ledEventGroup, LED_STATE_NORMAL_PAUZED);
    }
    else
    {
        WSMessage message = {.targetLiters = this->litersTarget};
        xQueueSend(toWSQueue, (void *)&message, pdMS_TO_TICKS(50));

        digitalWrite(PIN_RELAY_OUT, HIGH);
        lcd->print("System running  ");
        xEventGroupClearBits(ledEventGroup, 0xff);
        xEventGroupSetBits(ledEventGroup, LED_STATE_NORMAL_RUNNIN);
    }
}
void DeviceModeRunning::setLiters(double liters)
{
    this->litersCount = liters;

    lcd->setCursor(1, 0);
    uint64_t number = ((uint64_t)liters * 10) / 10;
    uint64_t decimals = (liters - (double)number) * 10;
    lcd->print(number, DEC);
    lcd->print(".");
    lcd->print(decimals, DEC);

    if (liters >= this->litersTarget && this->litersTarget > 0)
    {
        // We're done :)
        (*this->onDoneCallback)(this->litersCount);
    }
}
void DeviceModeRunning::pressedLong()
{
    (*this->onExitCallback)();
}
void DeviceModeRunning::tick()
{
}