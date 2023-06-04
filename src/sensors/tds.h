#pragma once
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#ifndef TDS_H
#define TdsSensorPin 33
#define DS18B20Pin 19 //DS18B20 Pin
#define VREF 3.3  // analog reference voltage(Volt) of the ADC
#define SCOUNT 30 // sum of sample point

int analogBuffer[SCOUNT]; // store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0;
int copyIndex = 0;

float averageVoltage = 0;
float tdsValue = 0;
float temperature = 25;

OneWire oneWire(DS18B20Pin);
DallasTemperature DS18B20(&oneWire);
float waterTemp;

void setupTdsSensor()
{
    pinMode(TdsSensorPin, INPUT);

}

int getMedianNum(int bArray[], int iFilterLen)
{
    int bTab[iFilterLen];
    for (byte i = 0; i < iFilterLen; i++)
        bTab[i] = bArray[i];
    int i, j, bTemp;
    for (j = 0; j < iFilterLen - 1; j++)
    {
        for (i = 0; i < iFilterLen - j - 1; i++)
        {
            if (bTab[i] > bTab[i + 1])
            {
                bTemp = bTab[i];
                bTab[i] = bTab[i + 1];
                bTab[i + 1] = bTemp;
            }
        }
    }
    if ((iFilterLen & 1) > 0)
    {
        bTemp = bTab[(iFilterLen - 1) / 2];
    }
    else
    {
        bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
    }
    return bTemp;
};

void getSensorValue()
{
    DS18B20.requestTemperatures();
    waterTemp = DS18B20.getTempCByIndex(0);
    for (int i = 0; i < 30; i++)
    {
        analogBuffer[i] = analogRead(TdsSensorPin);
        delay(10);
    }
}

void getTdsValue()
{
    getSensorValue();
    // read the analog value more stable by the median filtering algorithm, and convert to voltage value
    averageVoltage = getMedianNum(analogBuffer, 30) * (float)VREF / 4095.0;

    // temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
    float compensationCoefficient = 1.0 + 0.02 * (waterTemp - 25.0);
    // temperature compensation
    float compensationVoltage = averageVoltage / compensationCoefficient;

    // convert voltage value to tds value
    tdsValue = (133.42 * compensationVoltage * compensationVoltage * compensationVoltage - 255.86 * compensationVoltage * compensationVoltage + 857.39 * compensationVoltage) * 0.5;
    Serial.print("TDS Value:");
    Serial.print(tdsValue, 0);
    Serial.println("ppm");
};
#endif