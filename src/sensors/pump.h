#pragma once
#include <Arduino.h>
#ifndef PUMPS
#define PUMPS
#define PUMP_5V 22
#define PUMP_12V 23
#endif

void controlPumps(int pump, uint8_t state)
{
    switch (pump)
    {
    case 5:
        digitalWrite(PUMP_5V, state);
        break;
    case 12:
        digitalWrite(PUMP_12V, state);
        break;
    default:
        break;
    }
}

void setupPumps()
{
    pinMode(PUMP_5V, OUTPUT);
    pinMode(PUMP_12V, OUTPUT);
}