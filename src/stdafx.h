#include "sensors/pump.h"
#include "sensors/water-sensor.h"
#include "sensors/dht.h"
#include "sensors/tds.h"
#include "sensors/hc-sr04.h"
#include "features.h"

hw_timer_t *timer = NULL; // khơi tạo timer
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
int count = 0;
struct SensorData
{
    float tdsValue;
    float temperature;
    float humidity;
    float distanceCm;
    float waterLevel;
    float waterTemp;
    bool isPump1OnPrevious;
};

SensorData sensorData;

void setupSensors()
{
    Serial.begin(9600);
    delay(3000); // wait for the serial to be opened
    sensorData.distanceCm = 9;
    setupTdsSensor();
    setupWaterLevelSensor();
    setupDHT();
    setupSonic();
    setupPumps();
    initWifi();
    initThingSpeak();
}

void getData()
{
    sensorData.humidity = dht.readHumidity();
    sensorData.temperature = dht.readTemperature();
    sensorData.tdsValue = getTdsValue();
    sensorData.distanceCm = readHcSr04Avg();
    sensorData.waterLevel = readWaterLevelSensor();
    sensorData.waterTemp = getWaterTemperature();
}

void handleSensorData();
void handleWaterHeight();
void setupTimer();

// hàm xử lý ngắt
void IRAM_ATTR onTimer();