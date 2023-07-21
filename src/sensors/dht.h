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

float air_Temperature[10];
float air_Humidity[10];

float averageHumidity = 0;
float averageTemperature = 0;
int indexDHT = 0;
bool isInitialized = false;

void setupDHT()
{
    dht.begin();
}

void initialValues()
{
    for (int i = 0; i < 10; i++)
    {
        air_Humidity[i] = dht.readHumidity();
        air_Temperature[i] = dht.readTemperature();
        averageHumidity += air_Humidity[i];
        averageTemperature += air_Temperature[i];
    }
    averageHumidity /= 10;
    averageTemperature /= 10;
    isInitialized = true;
}

void getDhtData()
{
    if (!isInitialized)
    {
        initialValues();
    }

    air_Humidity[indexDHT] = dht.readHumidity();
    air_Temperature[indexDHT] = dht.readTemperature();

    averageHumidity = (averageHumidity * 10 - air_Humidity[indexDHT + 1] + air_Humidity[indexDHT]) / 10;
    averageTemperature = (averageTemperature * 10 - air_Temperature[indexDHT + 1] + air_Temperature[indexDHT]) / 10;

    indexDHT++;
    if (indexDHT == 10)
    {
        indexDHT = 0;
    }
}

float getAirTemperature()
{
    return averageTemperature;
}

float getAirHumidity()
{
    return averageHumidity;
}
