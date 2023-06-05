#pragma once
#include "WiFi.h"
#include "ThingSpeak.h"

#define CHANNEL_ID 2141870

const float HEIGHT_OF_SENSOR = 32.5;

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
    ThingSpeak.setField(1, humidity);
    ThingSpeak.setField(2, temperature);
    ThingSpeak.setField(3, tdsValue);
    ThingSpeak.setField(4, HEIGHT_OF_SENSOR - distanceCm);
    ThingSpeak.setField(5, waterTemp);
    ThingSpeak.writeFields(CHANNEL_ID, write_api_key);
    Serial.println("Data sent to ThingSpeak");
}

void printData (float humidity, float airTemp, float waterTemp, float tdsValue, float distanceCm){
  Serial.print("Air Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Air Temperature: ");
  Serial.print(airTemp);
  Serial.println(" *C ");
  Serial.print("Water Temperature: ");
  Serial.print(waterTemp);
  Serial.print("TDS Value: ");
  Serial.print(tdsValue);
  Serial.println(" ppm ");
  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.print(" cm ");
  Serial.println();
}