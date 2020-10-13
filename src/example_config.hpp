#ifndef CONFIG_DEF
#define CONFIG_DEF

#define NUM_LEDS 120
#define DOUBLE_FOR_EACH true
#define LED_PIN 5 
#define BLINK_BRIGHTNESS 0.7
#define DIMM_VALUE 0xFF
#define DIMM_ADD_VALUE 0xAA

// Touch Pin
#define THRESHOLD 39
#define SMOOTH_LOOPS 50
#define TOUCH_PIN 4

#pragma region display settings
#define DISPLAY_TEMPERATURE
#define DISPLAY_PRESSURE
// in ms
#define ENV_DISPLAY_TIME 2000
#define PHOTORESISTOR_PIN 21
#pragma endregion

#pragma region sensors
#define LIGHT_SENSOR
#define TEMPERATURE_SENSOR
#define HUMIDITY_SENSOR
#define PRESSURE_SENSOR
#pragma endregion

#pragma region used sensors
#define BME280
#pragma endregion

#endif