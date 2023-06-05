#include "sensors/pump.h"
#include "sensors/water-sensor.h"
#include "sensors/dht.h"
#include "sensors/tds.h"
#include "sensors/hc-sr04.h"
#include "features.h"

#define uS_TO_S_FACTOR 1000000 /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 1800     /* Time ESP32 will go to sleep (in seconds) */
int count = 1;
hw_timer_t *timer = NULL; // khơi tạo timer
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
float oldDistance = 0.0;
float oldTdsValue = 0.0;

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

RTC_DATA_ATTR SensorData sensorData;

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
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    readHcSr04();
    getTdsValue();

    oldDistance = sensorData.distanceCm;
    oldTdsValue = sensorData.tdsValue;
    
    sensorData.humidity = h;
    sensorData.temperature = t;
    sensorData.tdsValue = tdsValue;
    sensorData.distanceCm = distanceCm;
    sensorData.waterLevel = waterLevel;
    sensorData.waterTemp = waterTemp;
}

void handleSensorData();
void handleWaterHeight();
void setupTimer();

// hàm xử lý ngắt
void IRAM_ATTR onTimer();