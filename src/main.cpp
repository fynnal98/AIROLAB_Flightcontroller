#include <Arduino.h>
#include "ConfigManager.h"
#include "Logger.h"
#include "RemoteControllHandler.h"
#include "SensorManager.h"


using namespace flightcontroller;

void setup() {
    Serial.begin(115200); 
    delay(500);


    LOG_INFO("setup starting...");

    //Logger
    Logger::GetInstance().SetLevel(E_LogLevel::DEBUG);

    //ConfigManager
    if (!ConfigManager::GetInstance().load("/config.json")){
        LOG_WARNING("Standart parameter used!");
    }
    ConfigManager::GetInstance().printConfig();

    //RemoteControlHandler
    int sbus_rx = ConfigManager::GetInstance().get<int>("sbus/settings/rx");
    RemoteControlHandler::GetInstance().begin(sbus_rx); 

    //Sensorik
    int sda = ConfigManager::GetInstance().get<int>("sensors/settings/sda");
    int scl = ConfigManager::GetInstance().get<int>("sensors/settings/scl");
    float seaLevel = ConfigManager::GetInstance().get<float>("sensors/settings/seaLevel");
    SensorManager::GetInstance()->begin(sda, scl, seaLevel);

    LOG_INFO("setup done___________________________");
}

void loop() {
    //RemoteControlHandler 
    RemoteControlHandler::GetInstance().update();

    //Sensorik
    auto sensorManager = SensorManager::GetInstance();

    sensorManager->update();
    auto gyroX = sensorManager->GetMPU()->GetGyroX();
    auto gyroY = sensorManager->GetMPU()->GetGyroY();
    auto gyroZ = sensorManager->GetMPU()->GetGyroZ();

    LOG_DEBUG("GYRO| X: " + String(gyroX) + " Y: " + String(gyroY) + " Z: " + String(gyroZ));



    delay(50);

}
