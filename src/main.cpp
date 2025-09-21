#include <Arduino.h>
#include "BMP280Handler.h"
#include "ConfigManager.h"
#include "RemoteControllHandler.h"
#include "Logger.h"
#include "MPU6050Handler.h"


using namespace flightcontroller;

void setup() {
    Serial.begin(115200);
    delay(500);

    LOG_INFO("setup starting...");

    //Logger
    Logger::getInstance().setLevel(E_LogLevel::DEBUG);

    //ConfigManager
    if (!ConfigManager::getInstance().load("/config.json")){
        LOG_WARNING("Standart parameter used!");
    }
    ConfigManager::getInstance().printConfig();

    //RemoteControlHandler
    int sbus_rx = ConfigManager::getInstance().get<int>("sbus/settings/rx");
    RemoteControlHandler::getInstance().begin(sbus_rx); 

    //Sensorik
    int sda = ConfigManager::getInstance().get<int>("sensors/settings/sda");
    int scl = ConfigManager::getInstance().get<int>("sensors/settings/scl");
    if (!MPU6050Handler::getInstance().begin(sda, scl)) {
        LOG_ERROR("MPU6050 init failed!");
    }
    if (!BMP280Handler::getInstance().begin(sda, scl)) {
        LOG_ERROR("BMP280 init failed!");
    }

    LOG_INFO("setup done___________________________");
}

void loop() {
    //RemoteControlHandler 
    RemoteControlHandler::getInstance().update();
    //debug
    int16_t raw = RemoteControlHandler::getInstance().getChannelRaw(1);
    Serial.printf("Ch1 raw: %d\n", raw);
    delay(20);

    //MPU6050Handler
    MPU6050Handler::getInstance().update();
    //debug
    Serial.printf("AccelX: %d, AccelY: %d, AccelZ: %d, MPU TEMP: %.2f\n", 
                  MPU6050Handler::getInstance().getAccelX(),
                  MPU6050Handler::getInstance().getAccelY(),
                  MPU6050Handler::getInstance().getAccelZ(),
                  MPU6050Handler::getInstance().getTemperature());

    //BMP280Handler
    BMP280Handler::getInstance().update(1010.0f); //aktuelle Meereshöhe in hPa angeben
    //debug
    Serial.printf("BMP280 Temp: %.2f C | Pressure: %.2f hPa | Altitude: %.2f m\n",
                  BMP280Handler::getInstance().getTemperature(),
                  BMP280Handler::getInstance().getPressure() / 100.0f,
                  BMP280Handler::getInstance().getAltitude());

    delay(100);

}
