#include "config.h"
#include <Arduino.h>
#include <freertos/task.h>
#include "tasks/wifi_task.h"
#include "tasks/default_task.h"
#include "tasks/flow_task.h"
#include "tasks/led_task.h"
#include "tasks/level_task.h"
#include <freertos/event_groups.h>
#include <freertos/queue.h>
#include "models/WSMessage.h"

TaskHandle_t defaultTaskHandle;
TaskHandle_t wifiTaskHandle;
TaskHandle_t flowTaskHandle;
TaskHandle_t ledTaskHandle;
TaskHandle_t levelTaskHandle;

EventGroupHandle_t meterEventGroup;
EventGroupHandle_t ledEventGroup;
EventGroupHandle_t levelEventGroup;
EventGroupHandle_t wiFiEventGroup;

QueueHandle_t litersCounterQueue;
QueueHandle_t toWSQueue;
QueueHandle_t doneLitersQueue;

void GPIO_Init();

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Initialing GPIO pins...");
  GPIO_Init();
  Serial.println("Pins initialised");

  meterEventGroup = xEventGroupCreate();
  ledEventGroup = xEventGroupCreate();
  levelEventGroup = xEventGroupCreate();
  wiFiEventGroup = xEventGroupCreate();

  litersCounterQueue = xQueueCreate(10, sizeof(double));
  doneLitersQueue = xQueueCreate(10, sizeof(double));
  toWSQueue = xQueueCreate(10, sizeof(WSMessage));

  xTaskCreate(StartWiFiTask, "WiFi Task", configMINIMAL_STACK_SIZE + 9000, NULL, 2, &wifiTaskHandle);
  xTaskCreate(StartFlowTask, "Flow Task", configMINIMAL_STACK_SIZE + 3000, NULL, 1, &flowTaskHandle);
  xTaskCreate(StartDefaultTask, "WiFi Task", configMINIMAL_STACK_SIZE + 1024, NULL, 1, &defaultTaskHandle);
  xTaskCreate(StartLEDTask, "LED Task", configMINIMAL_STACK_SIZE + 256, NULL, 3, &ledTaskHandle);
  xTaskCreate(StartLevelTask, "Level Task", configMINIMAL_STACK_SIZE + 256, NULL, 2, &levelTaskHandle);
}

void loop()
{
  delay(500); // Work is done in separate tasks
}

void GPIO_Init()
{
  pinMode(PIN_RESET_LCD, OUTPUT);
  pinMode(PIN_RELAY_OUT, OUTPUT);
  pinMode(PIN_LEVEL_IN, INPUT);

  // Set the default states of all pins
  digitalWrite(PIN_RESET_LCD, LOW);
  digitalWrite(PIN_RELAY_OUT, LOW);
}