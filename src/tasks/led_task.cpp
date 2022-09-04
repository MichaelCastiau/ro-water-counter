#include "led_task.h"

void StartLEDTask(void *args)
{
    Serial.println("Start LED Task...");
    JLed ledGreen(LED_NORMAL);
    JLed ledRed(LED_ERROR);
    JLed ledWiFi(LED_WIFI);
    JLed backlight(PIN_LCD_BACKLIGHT);

    ledGreen.Off().Update();
    ledRed.Off().Update();
    ledWiFi.Off().Update();

    JLed backlightSeq[] = {
        backlight.On(),
        backlight.DelayBefore(BACKLIGHT_IDLE_MS).FadeOff(1000)};

    JLedSequence seq(JLedSequence::eMode::SEQUENCE, backlightSeq);

    for (;;)
    {
        EventBits_t ledEvent = xEventGroupGetBits(ledEventGroup);

        switch (ledEvent)
        {
        case LED_STATE_IDLE:
        {

            ledGreen.Reset().On();
            ledRed.Reset().Off();
            xEventGroupClearBits(ledEventGroup, 0xff);
            break;
        }
        case LED_STATE_NORMAL_RUNNIN:
        {
            ledGreen.Reset().Breathe(2500).Forever();
            ledRed.Reset().Off();
            xEventGroupClearBits(ledEventGroup, 0xff);
            break;
        }
        case LED_STATE_NORMAL_PAUZED:
        {
            ledGreen.Reset().Blink(500, 500).Forever();
            ledRed.Reset().Off();
            xEventGroupClearBits(ledEventGroup, 0xff);
            break;
        }
        case LED_STATE_ERROR:
        {
            ledGreen.Reset().Off();
            ledRed.Reset().Blink(250, 250).Forever();
            xEventGroupClearBits(ledEventGroup, 0xff);
            break;
        }
        }

         if (ledEvent & EN_BACKLIGHT)
         {
             seq.Reset();
             xEventGroupClearBits(ledEventGroup, EN_BACKLIGHT);
         }

        if (xEventGroupGetBits(wiFiEventGroup) & WIFI_CONNECTED)
        {
            ledWiFi.FadeOn(500);
            xEventGroupClearBits(wiFiEventGroup, WIFI_CONNECTED);
        }

        ledGreen.Update();
        ledRed.Update();
        ledWiFi.Update();
        backlight.Update();
        seq.Update();

        vTaskDelay(pdMS_TO_TICKS(20));
    }
}