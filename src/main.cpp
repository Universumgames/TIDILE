#include <Arduino.h>
#include <FastLED.h>
#include <WiFi.h>
#include "TIDILE.hpp"
#include "helper.hpp"
#include "Handler.hpp"
#include "definements.hpp"
#if defined(LIGHT_SENSOR) || defined(TEMPERATURE_SENSOR) || defined(HUMIDITY_SENSOR) || defined(PRESSURE_SENSOR)
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#endif

#if defined(HUMIDITY_SENSOR) && defined(BME280)
Adafruit_BME280 bmp; // I2C
#endif

CRGB leds[NUM_LEDS];

TIDILE tidile;
AsyncWebServer server(HTTP_ENDPOINT_PORT);

ClockEnv getEnv()
{
  return ClockEnv {
#ifdef BME280
    temperature : bmp.readTemperature(),
    pressure : bmp.readPressure() / 100
#endif
  };
}

void setup()
{
  Serial.begin(115200);

  do // connect to wifi
  {
    WiFi.begin();
    delay(200);

    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.mode(WIFI_AP_STA);
      delay(500);
      WiFi.beginSmartConfig();
      int tries = 0;
      while (WiFi.status() != WL_CONNECTED)
      {
        delay(500);
        Serial.print(".");
        Serial.println(WiFi.smartConfigDone());
        tries++;
        if (tries > 50)
          ESP.restart();
      }
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }while(1 == 0);

#if defined(TEMPERATURE_SENSOR) || defined(HUMIDITY_SENSOR) || defined(PRESSURE_SENSOR)
  Wire.begin();
#ifdef HUMIDITY_SENSOR
  // BMP280
  bool ok = bmp.begin(0x76);
  if (!ok)
  {
    Serial.println("Could not find a valid BMP280!");
  }
#endif
#endif

  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  tidile.setup(leds, NUM_LEDS, &server);
  Helper.getTime();
}

int loopI = 0;
int touchAverage = 30;
long lightAvg = 0;
void loop()
{
  tidile.displayTime();

  if (loopI >= SMOOTH_LOOPS)
  {
#if defined(DISPLAY_HUMIDIY) || defined(DISPLAY_TEMPERATURE) || defined(DISPLAY_PRESSURE)
    if (touchAverage / SMOOTH_LOOPS < THRESHOLD)
    {
      tidile.displayEnv(getEnv());
    }
#endif
    lightAvg = lightAvg / SMOOTH_LOOPS;
    Serial.println(touchAverage / SMOOTH_LOOPS);
    // brighnest * (photo in % * influence in %)
    double lightPercent = (double)map(lightAvg, 0, 4095, 0, 100) / (double)100;
    double influence = (double)tidile.getConfig()->lightInfluence / (double)100;
    //Serial.print((1 / (lightPercent * influence + 1)));
#ifdef LIGHT_SENSOR
    double factor = influence * lightPercent + (1 - influence);
    FastLED.setBrightness(tidile.getConfig()->brightness * factor);
#else
    FastLED.setBrightness(tidile.getConfig()->brightness);
#endif
    //*/

    loopI = 0;
    touchAverage = 0;
    lightAvg = 0;
  }
  else
  {
    touchAverage += touchRead(TOUCH_PIN);
    lightAvg += analogRead(PHOTORESISTOR_PIN);
  }
  loopI++;
}
