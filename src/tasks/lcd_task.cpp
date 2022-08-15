#include "lcd_task.h"

extern EventGroupHandle_t modeGroup;

void StartLCDTask(void *args)
{
    std::unique_ptr<LCDMode> mode = std::unique_ptr<LCDMode>(new LCDModeMenu());
    Serial.println("Starting LCD task...");

    // Reset the LCD first
    digitalWrite(PIN_RESET_LCD, LOW);
    vTaskDelay(pdMS_TO_TICKS(500));
    digitalWrite(PIN_RESET_LCD, HIGH);

    LCD_ST7032 lcd;
    lcd.begin();
    lcd.setcontrast(60); // contrast value range is 0-63, try 25@5V or 50@3.3V as a starting value

    for (;;)
    {
        volatile EventBits_t mode = xEventGroupGetBits(modeGroup);
        if (mode & MODE_MENU)
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("RO Water Counter");
            lcd.setCursor(1, 0);
            lcd.print(0, DEC);
            lcd.setCursor(1, 3);
            lcd.print("Liters");
        }
        else if (mode & MODE_RUNNING)
        {
        }
        else if (mode & MODE_PAUZED)
        {
        }
        vTaskDelay(pdTICKS_TO_MS(50));
    }
}