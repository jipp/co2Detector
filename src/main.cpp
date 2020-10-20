#include <Arduino.h>

#include <iostream>

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
const int pin = 15;

#define OLED_RESET -1
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

CRGB leds[numLeds];
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()
{
  Serial.begin(SPEED);
  Wire.begin();
  FastLED.addLeds<WS2812, pin, GRB>(leds, numLeds);
  FastLED.setBrightness(32);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  display.setTextSize(2);
  display.setTextColor(WHITE);

  if (!scd30.begin())
  {
    std::cout << "Air sensor not detected. Please check wiring. Freezing..." << std::endl;
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

    std::cout << "co2(ppm): " << co2;
    std::cout << "; temp(C): " << scd30.getTemperature();
    std::cout << "; humidity(%): " << scd30.getHumidity() << std::endl;

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