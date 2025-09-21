#include "ConfigManager.h"

namespace flightcontroller {

ConfigManager::ConfigManager() {}

ConfigManager& ConfigManager::getInstance() {
    static ConfigManager instance;
    return instance;
}

bool ConfigManager::load(const char* path) {
    if (!LittleFS.begin()){
        LOG_ERROR("LittleFS failed!");
        return false;
    }

    File file = LittleFS.open(path, "r");
    if (!file){
        LOG_ERROR("no Config file");
        return false;
    }

    DeserializationError err = deserializeJson(m_doc, file);
    file.close();

    if (err) {
        LOG_ERROR("Config error:" + String(err.c_str()));
        return false;
    }

    LOG_INFO("Config loaded!");
    return true;
}

/// @brief helps to pars
/// @param path to the config parameter
/// @return current
JsonVariant ConfigManager::resolvePath(const String& path) {
    JsonVariant current = m_doc.as<JsonVariant>();
    int start = 0;
    while (start < path.length()) {
        int sep = path.indexOf('/', start);
        String key;
        if (sep == -1) {
            key = path.substring(start);
            start = path.length();
        } else {
            key = path.substring(start, sep);
            start = sep + 1;
        }
        if (!current.is<JsonObject>()) return JsonVariant();
        current = current[key];
    }
    return current;
}

}