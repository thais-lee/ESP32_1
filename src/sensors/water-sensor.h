#pragma once
#include <Arduino.h>
#ifndef WATER_LEVEL_SENSOR
#define WATER_LEVEL_SENSOR
#define WATER_LEVEL_SENSOR_PIN 35
#endif

float waterLevel;

void setupWaterLevelSensor()
{
    pinMode(WATER_LEVEL_SENSOR_PIN, INPUT);
}

float readWaterLevelSensor()
{
    waterLevel = analogRead(WATER_LEVEL_SENSOR_PIN);
    return waterLevel;
}
