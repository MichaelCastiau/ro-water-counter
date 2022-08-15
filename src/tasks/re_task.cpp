#include "re_task.h"

void StartRotaryEncoderTask(void* args)
{
    for (;;)
        vTaskDelay(pdTICKS_TO_MS(50));
}