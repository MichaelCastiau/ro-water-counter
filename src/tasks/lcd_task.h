#ifndef __LCD_TASK__
#define __LCD_TASK__

#include <Arduino.h>
#include <freertos/task.h>
#include <LCD_ST7032.h>
#include "../config.h"
#include <memory>
#include "../modes/lcd_mode.h"
#include "../modes/lcd_mode_menu.h"
#include <freertos/event_groups.h>

void StartLCDTask(void *args);

#endif