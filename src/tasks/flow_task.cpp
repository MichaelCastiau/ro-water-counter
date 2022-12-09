#include "flow_task.h"

void MeterISR();

extern EventGroupHandle_t meterEventGroup;
extern QueueHandle_t litersCounterQueue;
extern QueueHandle_t toWSQueue;

long pulseCount = 0;

void StartFlowTask(void *args)
{
    Serial.println("Starting flow meter task...");
    volatile uint32_t now, previousTime = 0;
    double totalVolume, previousTotalVolume = 0.0;

    static TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(FLOW_PERIOD_MS);
    static BaseType_t xWasDelayed;

    xLastWakeTime = xTaskGetTickCount();
    for (;;)
    {
        xWasDelayed = xTaskDelayUntil(&xLastWakeTime, xFrequency);
        detachInterrupt(PIN_FLOW_IN);

        const volatile EventBits_t meterEvent = xEventGroupGetBits(meterEventGroup);
        if (meterEvent & RESET_FLOW_METER)
        {
            Serial.println("Resetting flow meter");
            totalVolume, previousTotalVolume = 0;
            xQueueReset(litersCounterQueue);
            xEventGroupClearBits(meterEventGroup, RESET_FLOW_METER);
            pulseCount = 0;
        }

        uint64_t msPassed = FLOW_PERIOD_MS + (xWasDelayed ? pdTICKS_TO_MS(xTaskGetTickCount() - xLastWakeTime) : 0);
        double flowRate = ((1000.0 / msPassed) * pulseCount) / FLOW_METER_K_FACTOR;
        double currentVolume = (flowRate / 60);

        totalVolume += currentVolume;

        WSMessage message = {.flowRate = flowRate, .litersFilled = totalVolume, .count = pulseCount};
        xQueueSend(toWSQueue, (void *)&message, pdMS_TO_TICKS(100));

        Serial.printf("ms passed %i\ncurrent volume: %f\ntotalVolume: %f\n", msPassed, currentVolume, totalVolume);

        pulseCount = 0;
        if (totalVolume != previousTotalVolume)
        {
            Serial.printf("Total volume: %f\n", totalVolume);
            // Send to the default task to display
            xQueueSend(litersCounterQueue, (void *)&totalVolume, pdMS_TO_TICKS(5));
        }
        previousTotalVolume = totalVolume;

        attachInterrupt(PIN_FLOW_IN, MeterISR, CHANGE);
    }
}

void MeterISR()
{
    ++pulseCount;
}