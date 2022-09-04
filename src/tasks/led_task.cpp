#include "led_task.h"

void StartLEDTask(void *args)
{
    Serial.println("Start LED Task...");
    JLed ledGreen(LED_NORMAL);
    JLed ledRed(LED_ERROR);
    JLed ledWiFi(LED_WIFI);

    ledGreen.Off().Update();
    ledRed.Off().Update();
    ledWiFi.Off().Update();

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

        if (xEventGroupGetBits(wiFiEventGroup) & WIFI_CONNECTED)
        {
            ledWiFi.FadeOn(1000);
            xEventGroupClearBits(wiFiEventGroup, WIFI_CONNECTED);
        }

        ledGreen.Update();
        ledRed.Update();
        ledWiFi.Update();

        vTaskDelay(pdMS_TO_TICKS(20));
    }
}