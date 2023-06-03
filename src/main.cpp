#include "stdafx.h"

void setup()
{
  setupSensors();
  // esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  // handleSensorData();
  // Serial.flush();
  // esp_deep_sleep_start();
}

void loop()
{
  // handleSensorData();
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  readHcSr04();
  getTdsValue();

  sensorData.humidity = h;
  sensorData.temperature = t;
  sensorData.tdsValue = tdsValue;
  sensorData.distanceCm = distanceCm;

  Serial.print("Humidity: ");
  Serial.print(sensorData.humidity);
  Serial.print(" %\t");
  Serial.print("Air Temperature: ");
  Serial.print(sensorData.temperature);
  Serial.print(" *C ");
  Serial.print("Water Temperature: ");
  Serial.print(waterTemp);
  Serial.print("TDS Value: ");
  Serial.print(sensorData.tdsValue);
  Serial.print(" ppm ");
  Serial.print("Distance: ");
  Serial.print(sensorData.distanceCm);
  Serial.print(" cm ");
  Serial.println();

  // sendToThingSpeak(sensorData.tdsValue, sensorData.temperature, sensorData.humidity, sensorData.distanceCm);
  delay(10000);
}

void handleSensorData()
{
  sensorData.isPump1OnPrevious = false;
  Serial.print("Previous data: Humidity - ");
  Serial.print(sensorData.humidity);
  Serial.print(" Temperature - ");
  Serial.print(sensorData.temperature);
  Serial.print(" TDS - ");
  Serial.print(sensorData.tdsValue);
  Serial.println();

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  getTdsValue();
  readHcSr04();

  // if (sensorData.isPump1OnPrevious == true)
  // {
  //   do
  //   {
  //     readHcSr04();
  //   } while (distanceCm > 20.0);
  // }
  // else
  // {
  //   do
  //   {
  //     readHcSr04();
  //   } while (fabs(distanceCm - sensorData.distanceCm) > 1.5 || distanceCm < sensorData.distanceCm);
  // }

  sensorData.humidity = h;
  sensorData.temperature = t;
  sensorData.tdsValue = tdsValue;
  sensorData.distanceCm = distanceCm;

  Serial.print("New data: Humidity - ");
  Serial.print(sensorData.humidity);
  Serial.print(" Temperature - ");
  Serial.print(sensorData.temperature);
  Serial.print(" TDS - ");
  Serial.print(sensorData.tdsValue);
  Serial.println();

  // controlPumps(5, HIGH);
  // delay(1000 * 3 * 60); // 3 minutes
  // controlPumps(5, LOW);

  Serial.print("distanceCm: ");
  Serial.print(sensorData.distanceCm);

  sendToThingSpeak(sensorData.tdsValue, sensorData.temperature, sensorData.humidity, sensorData.distanceCm);

  if (sensorData.distanceCm > 10.0)
  {
    controlPumps(12, HIGH);
    handleWaterHeight();
  }

  Serial.println("Going to sleep now");
  delay(5000);
}

void handleWaterHeight()
{
  do
  {
    sensorData.waterLevel = analogRead(WATER_LEVEL_SENSOR_PIN);
    readHcSr04();
    sensorData.distanceCm = distanceCm;

    Serial.print("Water level: ");
    Serial.print(sensorData.waterLevel);
    Serial.print(" Distance: ");
    Serial.print(sensorData.distanceCm);
    Serial.println();
    delay(1000);
  } while (distanceCm > 6 && sensorData.waterLevel < 1000);
  controlPumps(12, LOW);
  sensorData.isPump1OnPrevious = true;
  sendToThingSpeak(sensorData.tdsValue, sensorData.temperature, sensorData.humidity, sensorData.distanceCm);
}
