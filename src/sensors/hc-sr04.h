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
    // Clears the trigPin
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(ECHO_PIN, HIGH);

    // Calculate the distance
    distanceCm = duration * SOUND_SPEED / 2;
    return distanceCm;
}
