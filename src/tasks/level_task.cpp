#include "level_task.h"

extern EventGroupHandle_t levelEventGroup;

void StartLevelTask(void *args)
{
    xEventGroupSetBits(levelEventGroup, WATER_TOPPED_OFF);

    for (;;)
    {
        uint8_t waterOnSensor = digitalRead(PIN_LEVEL_IN);
        EventBits_t event = xEventGroupGetBits(levelEventGroup);

        if (!waterOnSensor && (event & WATER_TOPPED_OFF))
        {
            xEventGroupClearBits(levelEventGroup, WATER_TOPPED_OFF);
        }
        else if (waterOnSensor && !(event & WATER_TOPPED_OFF))
        {
            // Topped off now
            xEventGroupSetBits(levelEventGroup, WATER_TOPPED_OFF);
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}