#include <Arduino.h>
#include <ConfigManager.h>
#include "Logger.h"

using namespace flightcontroller;

void setup() {
    Serial.begin(115200);
    delay(500);

    Serial.println("Flightcontroller starting...");

    flightcontroller::Logger::getInstance().setLevel(flightcontroller::E_LogLevel::DEBUG);

    if (!ConfigManager::getInstance().load()){
        LOG_WARNING("Standart parameter used!");
    }

    int sda = flightcontroller::ConfigManager::getInstance().get<int>("imu/i2c_sda", 8);
    LOG_INFO("sda gesetzt: " + String(sda));

}

void loop() {
    delay(2000);
}
