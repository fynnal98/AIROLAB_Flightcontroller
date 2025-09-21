#include <Arduino.h>
#include <ConfigManager.h>
#include <InputManager.h>
#include "Logger.h"

using namespace flightcontroller;

void setup() {
    Serial.begin(115200);
    delay(500);

    LOG_INFO("setup starting...");

    Logger::getInstance().setLevel(E_LogLevel::DEBUG);

    if (!ConfigManager::getInstance().load()){
        LOG_WARNING("Standart parameter used!");
    }

    int sbus_rx = ConfigManager::getInstance().get<int>("sbus/settings/rx");
    InputManager::getInstance().begin(sbus_rx); 
}

void loop() {
    InputManager::getInstance().update();
    int16_t raw = InputManager::getInstance().getChannelRaw(1);
    Serial.printf("Ch1 raw: %d\n", raw);
    delay(20);
}
