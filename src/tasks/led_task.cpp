#include "led_task.h"

void StartLEDTask(void *args)
{
    Serial.println("Start LED Task...");
    JLed ledGreen(LED_NORMAL);
    JLed ledRed(LED_ERROR);

    pinMode(LED_NORMAL, OUTPUT);
    pinMode(LED_ERROR, OUTPUT);
    digitalWrite(LED_NORMAL, HIGH);
    digitalWrite(LED_ERROR, HIGH);

    /*    ledGreen.Off(1).Update();
    ledRed.Off(1).Update();*/

    for (;;)
    {
        EventBits_t ledEvent = xEventGroupGetBits(ledEventGroup);

        switch (ledEvent)
        {
        case LED_STATE_IDLE:
        {
            digitalWrite(LED_NORMAL, HIGH);
            digitalWrite(LED_ERROR, HIGH);

            /* ledGreen.Reset().FadeOn(1000);
             ledRed.Reset().Off();*/
            xEventGroupClearBits(ledEventGroup, 0xff);
            break;
        }
        case LED_STATE_NORMAL_RUNNIN:
        {
            digitalWrite(LED_NORMAL, LOW);
            /*  ledGreen.Reset().Breathe(1000).Forever();
              ledRed.Reset().Off();*/
            xEventGroupClearBits(ledEventGroup, 0xff);
            break;
        }
        case LED_STATE_NORMAL_PAUZED:
        {
            digitalWrite(LED_NORMAL, HIGH);

            /* ledGreen.Reset().Blink(500, 500).Forever();
             ledRed.Reset().Off();*/
            xEventGroupClearBits(ledEventGroup, 0xff);
            break;
        }
        case LED_STATE_ERROR:
        {
            digitalWrite(LED_NORMAL, HIGH);
            digitalWrite(LED_ERROR, LOW);

            /*ledGreen.Reset().Off();
            ledRed.Reset().Blink(250, 250).Forever();*/
            xEventGroupClearBits(ledEventGroup, 0xff);
            break;
        }
        }

        //  ledGreen.Update();
        //  ledRed.Update();

        vTaskDelay(pdMS_TO_TICKS(20));
    }
}