#ifndef __RE_TASK__
#define __RE_TASK__

#include <Arduino.h>
#include <freertos/task.h>
#include "../config.h"
#include <SimpleRotary.h>
#include <freertos/event_groups.h>
#include <freertos/queue.h>


void StartRotaryEncoderTask(void* args);

#endif