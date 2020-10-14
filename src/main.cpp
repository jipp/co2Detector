#include <Arduino.h>

#include <iostream>

#include <Adafruit_NeoPixel.h>
#include <SparkFun_SCD30_Arduino_Library.h>
#include <Wire.h>

#ifndef SPEED
#define SPEED 460800
#endif

SCD30 scd30;

const int limit1 = 1000;
const int limit2 = 2000;
const int maxValue = 3200;
const int PIN = D3;
const int NUMPIXELS = 16;

Adafruit_NeoPixel neoPixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(SPEED);
  Wire.begin(D1, D2);
  neoPixels.begin();
  neoPixels.setBrightness(64);

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
    int CO2 = scd30.getCO2();

    if (CO2 > maxValue)
    {
      CO2 = maxValue;
    }
    neoPixels.clear();
    for (uint16_t i = 0; i < NUMPIXELS * CO2 / maxValue; i++)
    {
      if (i * 3 < NUMPIXELS)
      {
        neoPixels.setPixelColor(i, neoPixels.Color(0, 255, 0));
      }
      else if (i * 3 / 2 < NUMPIXELS)
      {
        neoPixels.setPixelColor(i, neoPixels.Color(255, 128, 0));
      }
      else
      {
        neoPixels.setPixelColor(i, neoPixels.Color(255, 0, 0));
      }
    }
    neoPixels.show(); // Send the updated pixel colors to the hardware.

    std::cout << "co2(ppm): " << CO2;
    std::cout << "; temp(C): " << scd30.getTemperature();
    std::cout << "; humidity(%):" << scd30.getHumidity() << std::endl;
  }

  delay(500);
}