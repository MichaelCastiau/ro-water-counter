#ifndef __LED_TASK_H__
#define __LED_TASK_H__

#include <Arduino.h>
#include <freertos/task.h>
#include <freertos/event_groups.h>
#include "../config.h"
#include <jled.h>

extern EventGroupHandle_t ledEventGroup;

void StartLEDTask(void *args);

#endif