#include <Arduino.h>

#include <iostream>

#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_SSD1306.h>
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
const uint16_t numPixels = 16;
const int pin = D3;
const uint16_t oledReset = 0;

Adafruit_NeoPixel neoPixels(numPixels, pin, NEO_GRB + NEO_KHZ800);
Adafruit_SSD1306 display(oledReset);

void setup()
{
  Serial.begin(SPEED);
  Wire.begin();
  neoPixels.begin();
  neoPixels.setBrightness(64);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
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

    neoPixels.clear();

    for (uint16_t i = 0; i < numPixels * co2 / maxValue; i++)
    {
      if (i * 3 < numPixels)
      {
        neoPixels.setPixelColor(i, neoPixels.Color(0, 255, 0));
      }
      else if (i * 3 / 2 < numPixels)
      {
        neoPixels.setPixelColor(i, neoPixels.Color(255, 128, 0));
      }
      else
      {
        neoPixels.setPixelColor(i, neoPixels.Color(255, 0, 0));
      }
    }

    neoPixels.show();

    std::cout << "co2(ppm): " << co2;
    std::cout << "; temp(C): " << scd30.getTemperature();
    std::cout << "; humidity(%): " << scd30.getHumidity() << std::endl;

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("co2(ppm):\n ");
    display.println(co2);
    display.print("temp(C):\n ");
    display.println(scd30.getTemperature());
    display.print("hum(%):\n ");
    display.println(scd30.getHumidity());
    display.display();
  }

  delay(500);
}