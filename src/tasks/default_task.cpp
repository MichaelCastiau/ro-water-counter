#include "default_task.h"

void StartDefaultTask(void *args)
{
    SimpleRotary encoder(RE_A, RE_B, RE_PRESS);

    volatile uint8_t rotation, singlePress = 0;
    volatile double litersCounter = 0;

    // Reset the LCD first
    digitalWrite(PIN_RESET_LCD, LOW);
    vTaskDelay(pdMS_TO_TICKS(500));
    digitalWrite(PIN_RESET_LCD, HIGH);

    LCD_ST7032 lcd;
    lcd.begin();
    lcd.setcontrast(60); // contrast value range is 0-63, try 25@5V or 50@3.3V as a starting value

    std::unique_ptr<DeviceMode> mode = std::unique_ptr<DeviceMode>(new DeviceModeMenu(&lcd));
    mode->initialise();

    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}
