#include <Arduino.h>
#include <WiFi.h>

#include "ConfigManager.h"
#include "Flightcontroller.h"
#include "Logger.h"
#include "RemoteControllHandler.h"
#include "SensorManager.h"
#include "TelemetryManager.h"


using namespace flightcontroller;

void setup() {
    Serial.begin(115200); 
    delay(500);


    LOG_INFO("setup starting...");

    //Logger
    Logger::GetInstance()->SetLevel(E_LogLevel::DEBUG);

    //ConfigManager
    auto config = ConfigManager::GetInstance();

    if (!config->Load("/config.json")){
        LOG_WARNING("Standart parameter used!");
    }
    delay(500);
    config->PrintConfig();
    delay(500);

    // WiFi AP
    String ssid = config->Get<String>("wifi/ssid");
    String passwd = config->Get<String>("wifi/password");

    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid.c_str(), passwd.c_str());

    IPAddress ip = WiFi.softAPIP();
    LOG_INFO("AP started. IP-Address: " + ip.toString());

    // FC
    Flightcontroller::GetInstance()->Begin();

    LOG_INFO("setup done___________________________");
}

void loop() {
    Flightcontroller::GetInstance()->Update();
    TelemetryManager::GetInstance()->SendTelemetryData();
    

    delay(50);
}
