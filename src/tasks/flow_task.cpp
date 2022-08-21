#include "flow_task.h"

void MeterISR();

extern EventGroupHandle_t meterEventGroup;
extern QueueHandle_t litersCounterQueue;

std::unique_ptr<FlowMeter> meter;

void StartFlowTask(void *args)
{
    // Flow operation of 5 liters,  Q factor of 73
    FlowSensorProperties YFS402 = {5.0f, 73.0f, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
    meter.reset(new FlowMeter(digitalPinToInterrupt(PIN_FLOW_IN), YFS402, MeterISR, RISING));

    Serial.println("Starting flow meter task...");
    volatile uint32_t now, previousTime = 0;
    double totalVolume, previousTotalVolume = 0.0;
    for (;;)
    {
        const volatile EventBits_t meterEvent = xEventGroupGetBits(meterEventGroup);
        if (meterEvent & RESET_FLOW_METER)
        {
            Serial.println("Resetting flow meter");
            meter->reset();
            xEventGroupClearBits(meterEventGroup, RESET_FLOW_METER);
        }

        meter->tick(FLOW_PERIOD_MS); // 10ms as defined in the task delay
        totalVolume = meter->getTotalVolume();

        if (totalVolume != previousTotalVolume)
        {
            
            // Send to the default task to display
            xQueueSend(litersCounterQueue, (void *)&totalVolume, pdMS_TO_TICKS(5));
        }
        previousTotalVolume = totalVolume;

        vTaskDelay(pdMS_TO_TICKS(FLOW_PERIOD_MS));
    }
}

void MeterISR(){
    if(meter && meter.get()){
        meter->count();
    }
}