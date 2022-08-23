#include "flow_task.h"

void MeterISR();

extern EventGroupHandle_t meterEventGroup;
extern QueueHandle_t litersCounterQueue;

std::unique_ptr<FlowMeter> meter;

void StartFlowTask(void *args)
{
    FlowSensorProperties YFS402 = {5.0f, FLOW_METER_K_FACTOR, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
    meter.reset(new FlowMeter(digitalPinToInterrupt(PIN_FLOW_IN), YFS402, MeterISR, RISING));

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

        uint64_t msPassed = FLOW_PERIOD_MS; // + (xWasDelayed ? pdTICKS_TO_MS(xTaskGetTickCount() - xLastWakeTime) : 0);
        meter->tick(msPassed);              // 10ms as defined in the task delay

        const volatile EventBits_t meterEvent = xEventGroupGetBits(meterEventGroup);
        if (meterEvent & RESET_FLOW_METER)
        {
            Serial.println("Resetting flow meter");
            meter->reset();
            xEventGroupClearBits(meterEventGroup, RESET_FLOW_METER);
        }

        totalVolume = meter->getTotalVolume();

        if (totalVolume != previousTotalVolume)
        {
            Serial.printf("Total volume: %f\n", totalVolume);
            // Send to the default task to display
            xQueueSend(litersCounterQueue, (void *)&totalVolume, pdMS_TO_TICKS(5));
        }
        previousTotalVolume = totalVolume;
    }
}

void MeterISR()
{
    if (meter && meter.get())
    {
        meter->count();
    }
}