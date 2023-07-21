#include "stdafx.h"

void setup()
{
  setupSensors();
}

void loop()
{
  getData();
  printData(sensorData.humidity, sensorData.temperature, sensorData.waterTemp, sensorData.tdsValue, sensorData.distanceCm);
  Serial.print("Water Level: ");
  Serial.println(sensorData.waterLevel);
  if (sensorData.distanceCm > 6)
  {
    // sendToThingSpeak(sensorData.tdsValue, sensorData.temperature, sensorData.humidity, sensorData.distanceCm, sensorData.waterTemp);
    controlPumps(12, HIGH);
    handleWaterHeight();
  }

  count++;
  if (count == 30)
  {
    controlPumps(5, HIGH);
    delay(1000 * 3); // 3 seconds
    controlPumps(5, LOW);
    sendToThingSpeak(sensorData.tdsValue, sensorData.temperature, sensorData.humidity, sensorData.distanceCm, sensorData.waterTemp);
    count = 0;
  }
  delay(3000);
}

void handleWaterHeight()
{
  do
  {
    sensorData.waterLevel = readWaterLevelSensor();
    Serial.print("Water Level: ");
    Serial.println(sensorData.waterLevel);
    sensorData.distanceCm = readHcSr04();
    Serial.print("Distance: ");
    Serial.println(sensorData.distanceCm);
    delay(300);
  } while (sensorData.distanceCm > 5 && sensorData.waterLevel < 10);
  controlPumps(12, LOW);

  sendToThingSpeak(sensorData.tdsValue, sensorData.temperature, sensorData.humidity, sensorData.distanceCm, sensorData.waterTemp);
}

