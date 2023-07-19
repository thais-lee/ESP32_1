#include "stdafx.h"

void setup()
{
  setupSensors();
  // setupTimer();
}

void loop()
{
  getData();
  sendToThingSpeak(sensorData.tdsValue, sensorData.temperature, sensorData.humidity, sensorData.distanceCm, sensorData.waterTemp);
  // handleSensorData();
  // printData(sensorData.humidity, sensorData.temperature, sensorData.waterTemp, sensorData.tdsValue, sensorData.distanceCm);
  delay(1000 * 60 * 7);
  // delay(3000);
}

// void handleSensorData()
// {
//   if (sensorData.distanceCm > 11.0)
//   {
//     sendToThingSpeak(sensorData.tdsValue, sensorData.temperature, sensorData.humidity, sensorData.distanceCm, sensorData.waterTemp);
//     controlPumps(12, HIGH);
//     handleWaterHeight();
//   }

//   if (sensorData.distanceCm < oldDistance)
//   {
//     sendToThingSpeak(sensorData.tdsValue, sensorData.temperature, sensorData.humidity, sensorData.distanceCm, sensorData.waterTemp);
//     controlPumps(12, LOW);
//   }

//   if(sensorData.distanceCm > oldTdsValue) {
//     sendToThingSpeak(sensorData.tdsValue, sensorData.temperature, sensorData.humidity, sensorData.distanceCm, sensorData.waterTemp);
//   }
// }

// void handleWaterHeight()
// {
//   do
//   {
//     sensorData.waterLevel = analogRead(WATER_LEVEL_SENSOR_PIN);
//     readHcSr04();
//     sensorData.distanceCm = distanceCm;

//     Serial.print("Water level: ");
//     Serial.print(sensorData.waterLevel);
//     Serial.print(" Distance: ");
//     Serial.print(sensorData.distanceCm);
//     Serial.println();
//     delay(1000);
//   } while (distanceCm > 6 && sensorData.waterLevel < 1000);
//   controlPumps(12, LOW);
//   sensorData.isPump1OnPrevious = true;
//   sendToThingSpeak(sensorData.tdsValue, sensorData.temperature, sensorData.humidity, sensorData.distanceCm, sensorData.waterTemp);
// }

// void IRAM_ATTR onTimer()
// {
//   portENTER_CRITICAL_ISR(&timerMux); // vào chế độ tránh xung đột

//   getData();
//   controlPumps(5, HIGH);
//   delay(1000 * 3 * 60); // 3 minutes
//   controlPumps(5, LOW);
//   sendToThingSpeak(sensorData.tdsValue, sensorData.temperature, sensorData.humidity, sensorData.distanceCm, sensorData.waterTemp);

//   portEXIT_CRITICAL_ISR(&timerMux); // thoát
// }

// void setupTimer()
// {
//   // khơit tạo timer với chu kì 1us vì thạch anh của ESP chạy 8MHz
//   timer = timerBegin(0, 80, true);
//   // khởi tạo hàm xử lý ngắt ngắt cho Timer
//   timerAttachInterrupt(timer, &onTimer, true);
//   // khởi tạo thời gian ngắt cho timer là 10 minutes (1s = 1000000 us)
//   timerAlarmWrite(timer, 60 * 10 * 1000000, true); // 10 minutes
//   // bắt đầu chạy timer
//   timerAlarmEnable(timer);
// }
