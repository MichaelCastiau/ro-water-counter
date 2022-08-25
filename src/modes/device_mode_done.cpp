#include "device_mode_done.h"

DeviceModeDone::DeviceModeDone(LCD_ST7032 *lcd, double litersFilled, std::function<void(void)> *resetCallback)
{
    this->lcd = lcd;
    this->litersFilled = litersFilled;
    this->onResetCallback = resetCallback;
}
DeviceModeDone::~DeviceModeDone() {}

void DeviceModeDone::initialise()
{
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Done");
    lcd->setCursor(1, 0);
    lcd->print("Filled ");

    uint64_t numberLiters = ((uint64_t)litersFilled * 10) / 10;
    uint64_t decimalsLiters = (litersFilled - (double)numberLiters) * 10;

    lcd->print(numberLiters, DEC);
    lcd->print(".");
    lcd->print(decimalsLiters, DEC);
    lcd->print("l");

    digitalWrite(PIN_RELAY_OUT, LOW);
    xQueueSend(doneLitersQueue, (void *)&litersFilled, pdMS_TO_TICKS(50));
}
void DeviceModeDone::rotatedClockwise(void) {}
void DeviceModeDone::rotatedCounterClockwise(void) {}
void DeviceModeDone::setLiters(double liters) {}
void DeviceModeDone::pressed(void)
{
    (*this->onResetCallback)();
}
void DeviceModeDone::pressedLong()
{
}
void DeviceModeDone::tick(){}