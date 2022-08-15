#define PIN_RESET_LCD       2
#define PIN_RELAY_OUT       12
#define PIN_LCD_BACKLIGHT   16
#define PIN_LEVEL_IN        18
#define PIN_FLOW_IN         19
#define SW_PRESS            25  // rotary encoder press
#define RE_A                26  // rotary encoder A
#define RE_B                27  // rotary encoder B
#define LED_ERROR           32
#define LED_NORMAL          33

// Modes
#define MODE_MENU           (uint8_t)(1 << 1)
#define MODE_RUNNING        (uint8_t)(1 << 2)
#define MODE_PAUZED         (uint8_t)(1 << 3)