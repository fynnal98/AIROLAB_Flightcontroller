#pragma once
#include <Arduino.h>
#include <string>
#include <memory>

namespace flightcontroller {

enum class E_LogLevel {
    //only log errors
    ERROR = 0,
    // warning and errors
    WARNING = 1,
    //log informational message, error, warning
    INFO = 2,
    //all
    DEBUG = 3
};

class Logger {
public:
    //Singleton

    static std::shared_ptr<Logger> GetInstance(){
        static std::shared_ptr<Logger> instance = nullptr;
        if(!instance){
            instance = std::shared_ptr<Logger> (new Logger());
        }
        return instance;
    }

    /// Set the LogLevel 
    void SetLevel(E_LogLevel level) { 
        m_level = level; 
    }

    void Log(E_LogLevel level, const char* file, int line, const char* func, const String& msg) {
        if (level > m_level) return;

        String levelStr;
        String color;

        switch (level) {
            case E_LogLevel::ERROR:   
                levelStr = "ERROR";
                color = "\033[1;31m";
                break;
            case E_LogLevel::WARNING: 
                levelStr = "WARNING"; 
                color = "\033[33m";
                break;
            case E_LogLevel::INFO:    
                levelStr = "INFO"; 
                color = "\033[32m";
                break;
            case E_LogLevel::DEBUG:   
                levelStr = "DEBUG"; 
                color = "\033[34m";
                break;
        }

        // Timestamp
        unsigned long ms = millis();

        // Log-msg
        String logMsg = "[" + String(ms) + "ms|" + levelStr + "|" + file + ":" + line + "|" + func + "] " + msg;

        // Serial
        Serial.print(color);
        Serial.println(logMsg);
        Serial.println("\033[0m"); //reset color

        // TODO: optional per UDP zur Groundstation senden
    }

private:
    Logger() : m_level(E_LogLevel::DEBUG) {}
    E_LogLevel m_level;
};

// Convenience-Makros
#define LOG_ERROR(msg)   flightcontroller::Logger::GetInstance()->Log(flightcontroller::E_LogLevel::ERROR, __FILE__, __LINE__, __func__, msg)
#define LOG_WARNING(msg) flightcontroller::Logger::GetInstance()->Log(flightcontroller::E_LogLevel::WARNING, __FILE__, __LINE__, __func__, msg)
#define LOG_INFO(msg)    flightcontroller::Logger::GetInstance()->Log(flightcontroller::E_LogLevel::INFO, __FILE__, __LINE__, __func__, msg)
#define LOG_DEBUG(msg)   flightcontroller::Logger::GetInstance()->Log(flightcontroller::E_LogLevel::DEBUG, __FILE__, __LINE__, __func__, msg)

} 
