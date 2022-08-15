#include "config.h"
#include <Arduino.h>
#include <freertos/task.h>
#include "tasks/leds_task.h"
#include "tasks/re_task.h"
#include "tasks/lcd_task.h"
#include <freertos/event_groups.h>
#include <freertos/queue.h>

TaskHandle_t startRotaryEncoderTaskHandle;
TaskHandle_t startLCDTaskHandle;
EventGroupHandle_t modeGroup;
QueueHandle_t litersCounterQueue;

void GPIO_Init();

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Initialing GPIO pins...");
  GPIO_Init();
  Serial.println("Pins initialised");

  modeGroup = xEventGroupCreate();
  xEventGroupClearBits(modeGroup, 0xff);
  xEventGroupSetBits(modeGroup, MODE_MENU);

  litersCounterQueue = xQueueCreate(10, sizeof(double));

  xTaskCreate(StartRotaryEncoderTask, "RE Task", configMINIMAL_STACK_SIZE + 500, NULL, 1, &startRotaryEncoderTaskHandle);
  xTaskCreate(StartLCDTask, "LCD Task", configMINIMAL_STACK_SIZE + 500, NULL, 1, &startLCDTaskHandle);
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
  pinMode(PIN_FLOW_IN, INPUT);

  // PWM configuration
  ledcAttachPin(PIN_LCD_BACKLIGHT, 0); // Channel 0
  ledcSetup(0, 1000, 8);               // 1kHz frequency, 8 bit timer resolution

  pinMode(LED_ERROR, OUTPUT_OPEN_DRAIN);
  pinMode(LED_NORMAL, OUTPUT_OPEN_DRAIN);

  // Set the default states of all pins
  digitalWrite(PIN_RESET_LCD, LOW);
  digitalWrite(PIN_RELAY_OUT, LOW);

  analogWrite(PIN_LCD_BACKLIGHT, 204); // 80% duty cycle for setting brightness
  digitalWrite(LED_ERROR, HIGH);         // switch them off
  digitalWrite(LED_NORMAL, HIGH);
}