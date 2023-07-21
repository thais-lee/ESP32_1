#pragma once
#include <Arduino.h>

#ifndef SONIC_SENSOR
#define SONIC_SENSOR
#define TRIGGER_PIN 5
#define ECHO_PIN 18
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701
#endif

long duration;
float distanceCm;

void setupSonic()
{
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

float readHcSr04()
{
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH);
    return duration * SOUND_SPEED / 2;
}

float readHcSr04Avg()
{
    float tempDistanceCm[20] = {0};
    for (int i = 0; i < 20; i++)
    {
        tempDistanceCm[i] = readHcSr04();
        delay(50);
    }
    float sum = 0;
    for (int i = 0; i < 20; i++)
    {
        sum += tempDistanceCm[i];
    }
    distanceCm = sum / 20;
    return distanceCm;
}
