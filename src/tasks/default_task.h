#ifndef __DEFAULT_TASK_H__
#define __DEFAULT_TASK_H__

#include <Arduino.h>
#include <SimpleRotary.h>
#include "../config.h"
#include <LCD_ST7032.h>
#include "modes/device_mode_menu.h"
#include <memory>

void StartDefaultTask(void* args);

#endif