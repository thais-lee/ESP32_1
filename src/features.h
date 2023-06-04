#pragma once
#include "WiFi.h"
#include "ThingSpeak.h"

#define CHANNEL_ID 2141870
#define HEIGHT_OF_SENSOR 30

const char *ssid = "Tuan-712";
const char *password = "letuan1973";
const char *write_api_key = "WQ22GRWT8BE7MTWX";

WiFiClient client;

void initWifi()
{
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");
}

void initThingSpeak()
{
    ThingSpeak.begin(client);
}

void sendToThingSpeak(float tdsValue, float temperature, float humidity, float distanceCm)
{
    ThingSpeak.setField(1, humidity);
    ThingSpeak.setField(2, temperature);
    ThingSpeak.setField(3, tdsValue);
    ThingSpeak.setField(4, HEIGHT_OF_SENSOR - distanceCm);
    ThingSpeak.writeFields(CHANNEL_ID, write_api_key);
    Serial.println("Data sent to ThingSpeak");
}