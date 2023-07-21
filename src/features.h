#pragma once
#include "WiFi.h"
#include "ThingSpeak.h"

#define CHANNEL_ID 2141870

const float HEIGHT_OF_SENSOR = 26.5;

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

void sendToThingSpeak(float tdsValue, float temperature, float humidity, float distanceCm, float waterTemp)
{
    ThingSpeak.setField(1, dht.readHumidity());
    ThingSpeak.setField(2, dht.readTemperature());
    ThingSpeak.setField(3, tdsValue);
    ThingSpeak.setField(4, HEIGHT_OF_SENSOR - readHcSr04Avg());
    ThingSpeak.setField(5, waterTemp);
    ThingSpeak.setField(6, temperature);
    ThingSpeak.setField(7, HEIGHT_OF_SENSOR - distanceCm);
    ThingSpeak.setField(8, humidity);
    ThingSpeak.writeFields(CHANNEL_ID, write_api_key);
    Serial.println("Data sent to ThingSpeak");
}

void printData(float humidity, float airTemp, float waterTemp, float tdsValue, float distanceCm)
{
    Serial.print("Air Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t");
    Serial.print("Air Temperature: ");
    Serial.print(airTemp);
    Serial.print(" *C\t");
    Serial.print("Water Temperature: ");
    Serial.print(waterTemp);
    Serial.print(" *C\t");
    Serial.print("TDS Value: ");
    Serial.print(tdsValue);
    Serial.print(" ppm\t");
    Serial.print("Distance: ");
    Serial.print(distanceCm);
    Serial.print(" cm ");
    Serial.println();
    Serial.println("*********");
}