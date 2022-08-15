#include "re_task.h"

extern EventGroupHandle_t modeGroup;
extern QueueHandle_t litersCounterQueue;

void StartRotaryEncoderTask(void *args)
{
    SimpleRotary encoder(RE_A, RE_B, RE_PRESS);
    volatile uint8_t rotation, singlePress = 0;
    volatile double litersCounter = 0;
    for (;;)
    {
        volatile EventBits_t mode = xEventGroupGetBits(modeGroup);
        rotation = encoder.rotate();
        singlePress = encoder.push();

        if (mode & MODE_MENU)
        {
            switch (rotation)
            {
            case RE_ROTATE_CLOCKWISE:
            {
                // Add liters to the batch
                if (litersCounter < 50)
                {
                    litersCounter += 0.1;
                    xQueueSend(litersCounterQueue, (void *)&litersCounter, pdMS_TO_TICKS(25));
                }

                break;
            }
            case RE_ROTATE_COUNTERCLOCKWISE:
            {
                if (litersCounter > 0.2)
                {
                    litersCounter -= 0.1;
                    xQueueSend(litersCounterQueue, (void *)&litersCounter, pdMS_TO_TICKS(25));
                }

                // Remove liters from the batch
                break;
            }
            }

            if (singlePress & 1)
            {
                // We have now set our liters, switch mode
                xEventGroupClearBits(modeGroup, 0xff);
                xEventGroupSetBits(modeGroup, MODE_RUNNING);

                //TODO switch on the relais of course!
            }
        }
        vTaskDelay(pdTICKS_TO_MS(10));
    }
}