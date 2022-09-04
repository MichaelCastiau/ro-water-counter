#define PIN_RESET_LCD                   2
#define PIN_RELAY_OUT                   12
#define PIN_LCD_BACKLIGHT               16
#define PIN_LEVEL_IN                    18
#define PIN_FLOW_IN                     19
#define RE_PRESS                        25  // rotary encoder press
#define RE_A                            26  // rotary encoder A
#define RE_B                            27  // rotary encoder B
#define LED_ERROR                       32
#define LED_NORMAL                      33
#define LED_WIFI                        13

// Modes
#define MODE_MENU                       (uint8_t)(1 << 1)
#define MODE_RUNNING                    (uint8_t)(1 << 2)
#define MODE_PAUZED                     (uint8_t)(1 << 3)

// Rotary encoder
#define RE_STEPS                        (double) 0.5
#define RE_ROTATE_CLOCKWISE             (1 << 1)
#define RE_ROTATE_COUNTERCLOCKWISE      (1 << 0)

// FLow meter
#define FLOW_PERIOD_MS                   1000
#define RESET_FLOW_METER                 (1 << 0)
#define FLOW_METER_K_FACTOR              (double) 49.0

// LEDs events
#define LED_STATE_NORMAL_RUNNIN          (1 << 0)
#define LED_STATE_NORMAL_PAUZED          (1 << 1)
#define LED_STATE_ERROR                  (1 << 2)
#define LED_STATE_IDLE                   (1 << 3)

//LCD
#define BACKLIGHT_MAX                    203

// WiFi
#define WEBHOOKS_KEY                     (const char*)"bT83HL9K3aVx_YwVMMCmDC"
#define WIFI_CONNECTED                   (1 << 0)

// Water level
#define WATER_TOPPED_OFF                 (1 << 0)
