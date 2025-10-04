#pragma once 
#include <memory>
#include "ConfigManager.h"
#include <Arduino.h>
#include <ESP32Servo.h>

namespace flightcontroller{

    class ActuatorManager{
    public:
        static std::shared_ptr<ActuatorManager> GetInstance();

        bool Begin();
        void SetRoll(float value);
        void SetPitch(float value);
        void SetYaw(float value);
        void SetThrottle(float value);

    private:
        ActuatorManager();
        
        std::shared_ptr<ConfigManager> m_config;
        Servo m_servoRollRH;
        Servo m_servoRollLH;
        Servo m_servoPitch;
    };
}