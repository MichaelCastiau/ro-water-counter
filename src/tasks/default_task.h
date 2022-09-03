#ifndef __DEFAULT_TASK_H__
#define __DEFAULT_TASK_H__

#include <Arduino.h>
#include "../config.h"
#include <LCD_ST7032.h>
#include "modes/device_mode_menu.h"
#include "modes/device_mode_running.h"
#include "modes/device_mode_done.h"
#include "modes/device_mode_om.h"
#include "modes/device_mode_ato.h"
#include <memory>
#include <SimpleRotary.h>

void StartDefaultTask(void *args);

#endif