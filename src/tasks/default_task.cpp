#include "default_task.h"

extern QueueHandle_t litersCounterQueue;

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

    std::function<void(double)> goToRunning;
    std::function<void(void)> goToMenu;
    std::function<void(double)> goToDone;
    std::function<void(void)> startATO;

    std::unique_ptr<DeviceMode> mode = std::unique_ptr<DeviceMode>(new DeviceModeMenu(&lcd, &goToRunning));

    goToRunning = [&](double liters)
    {
        mode.reset(new DeviceModeRunning(&lcd, liters, &goToMenu, &goToDone));
        mode->initialise();
    };

    goToMenu = [&]()
    {
        mode.reset(new DeviceModeMenu(&lcd, &goToRunning));
        mode->initialise();
    };

    goToDone = [&](double litersFilled)
    {
        mode.reset(new DeviceModeDone(&lcd, litersFilled, &goToMenu));
        mode->initialise();
    };

    startATO = [&]
    {
        mode.reset(new DeviceModeATO(&lcd));
        mode->initialise();
    };

    mode->initialise();

    for (;;)
    {
        uint8_t rotation = encoder.rotate();
        uint8_t singlePress = encoder.push();
        uint8_t longPress = encoder.pushLong(3000);

        if (singlePress)
            mode->pressed();
        else if (rotation & RE_ROTATE_CLOCKWISE)
            mode->rotatedClockwise();
        else if (rotation & RE_ROTATE_COUNTERCLOCKWISE)
            mode->rotatedCounterClockwise();

        if (longPress)
            mode->pressedLong();

        if (uxQueueMessagesWaiting(litersCounterQueue) > 0)
        {
            double litersCounter = 0.0;
            xQueueReceive(litersCounterQueue, &litersCounter, pdMS_TO_TICKS(5));
            mode->setLiters(litersCounter);
        }

        vTaskDelay(pdMS_TO_TICKS(5));
    }
}
