#pragma once
#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#ifndef DHT_SENSOR

#define DHT_SENSOR
#define DHTPIN 21
#define DHTTYPE DHT22
#endif

DHT dht(DHTPIN, DHTTYPE);

void setupDHT()
{
    dht.begin();
}
