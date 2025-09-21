#pragma once 
#include <Arduino.h>
#include <ArduinoJson.h>
#include <FS.h>
#include <LittleFS.h>
#include <Logger.h>

namespace flightcontroller {

class ConfigManager{
public: 
    static ConfigManager& getInstance();

    void printConfig();

    bool load(const char* path);

    template<typename T> 
    T get(const String& path, T defaultValue = T()){
        JsonVariant v = resolvePath(path);
        if (!v.isNull() && v.is<T>()) {
            return v.as<T>();
        }
        return defaultValue;
    }

private: 
    ConfigManager();
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator = (const ConfigManager&) = delete;

    StaticJsonDocument<4096> m_doc; 
    // JsonDocument m_doc; //ohne Speicher begrenzung, geht aber nur bis 1KB
    JsonVariant resolvePath(const String& path);
};
}