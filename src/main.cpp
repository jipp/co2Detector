#include <Arduino.h>

//#include <iostream>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <FastLED.h>
#include <SparkFun_SCD30_Arduino_Library.h>
#include <SPI.h>
#include <Wire.h>

#ifndef SPEED
#define SPEED 115200
#endif

SCD30 scd30;

const uint16_t limit1 = 1000;
const uint16_t limit2 = 2000;
const uint16_t maxValue = 3200;
const uint16_t numLeds = 16;
const int dataPin = 13;

const int8_t oledReset = -1;
const uint8_t screenWidth = 128; // OLED display width, in pixels
const uint8_t screenHeight = 64; // OLED display height, in pixels

CRGB leds[numLeds];
Adafruit_SSD1306 display(screenWidth, screenHeight, &Wire, oledReset);

void setup()
{
  Serial.begin(SPEED);

  while (!Serial)
    ;

  Wire.begin();

  FastLED.addLeds<WS2812, dataPin, GRB>(leds, numLeds);
  FastLED.setBrightness(32);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  display.setTextSize(2);
  display.setTextColor(WHITE);

  if (!scd30.begin())
  {
    Serial.println("Air sensor not detected. Please check wiring. Freezing...");
    while (true)
    {
      ;
    }
  }
}

void loop()
{
  if (scd30.dataAvailable())
  {
    uint16_t co2 = scd30.getCO2();

    if (co2 > maxValue)
    {
      co2 = maxValue;
    }

    FastLED.clear();

    uint16_t normCo2 = co2 * numLeds / maxValue;
    uint16_t normLimit1 = limit1 * numLeds / maxValue;
    uint16_t normLimit2 = limit2 * numLeds / maxValue;

    for (uint16_t i = 0; i < numLeds; i++)
    {
      if (i < normCo2)
      {
        if (i < normLimit1)
        {
          leds[i] = CRGB::Green;
        }
        else if (i < normLimit2)
        {
          leds[i] = CRGB::Orange;
        }
        else
        {
          leds[i] = CRGB::Red;
        }
      }
    }

    FastLED.show();
    FastLED.delay(10);

    Serial.print("co2(ppm): ");
    Serial.print(co2);
    Serial.print("; temp(C): ");
    Serial.print(scd30.getTemperature());
    Serial.print("; humidity(%): ");
    Serial.println(scd30.getHumidity());

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(co2);
    display.println(" ppm");
    display.print(scd30.getTemperature());
    display.println(" C");
    display.print(scd30.getHumidity());
    display.println(" %");
    display.display();
  }

  delay(500);
}