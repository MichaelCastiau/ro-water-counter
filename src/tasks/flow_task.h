#ifndef __FLOW_TASK_H__
#define __FLOW_TASK_H__

#include <Arduino.h>
#include "../config.h"
#include <freertos/task.h>
#include <freertos/event_groups.h>
#include <memory>

void StartFlowTask(void* args);

#endif