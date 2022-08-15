#include "leds_task.h"

extern void StartLEDSTask()
{
    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(40));
    }
}