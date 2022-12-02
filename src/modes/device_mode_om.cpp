#include "device_mode_om.h"
DeviceModeOperationMode::DeviceModeOperationMode(LCD_ST7032 *lcd, std::function<void(void)> *startCounter, std::function<void(void)> *startATO)
{
    this->lcd = lcd;
    this->onStartCounter = startCounter;
    this->onStartATO = startATO;
}
DeviceModeOperationMode::~DeviceModeOperationMode()
{
}
void DeviceModeOperationMode::initialise()
{
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Choose Mode");
    lcd->setCursor(1, 0);
    lcd->print("(x)Counter( )ATO");
}
void DeviceModeOperationMode::rotatedClockwise(void)
{
    lcd->setCursor(1, 0);
    lcd->print("( )Counter(x)ATO");
    mode = ATO;
}
void DeviceModeOperationMode::rotatedCounterClockwise(void)
{
    lcd->setCursor(1, 0);
    lcd->print("(x)Counter( )ATO");
    mode = COUNTER;
}
void DeviceModeOperationMode::pressed(void)
{

    if (mode == COUNTER)
        (*this->onStartCounter)();
    else if (mode == ATO)
        (*this->onStartATO)();
}
void DeviceModeOperationMode::pressedLong(void) {}
void DeviceModeOperationMode::tick(void) {}
void DeviceModeOperationMode::setLiters(double liters) {}