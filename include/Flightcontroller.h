#pragma once 

#include <memory>

#include "Logger.h"
#include "SensorManager.h"
#include "ConfigManager.h"
#include "RemoteControllHandler.h"
#include "ActuatorManager.h"

namespace flightcontroller{

class Flightcontroller{
public: 
    static std::shared_ptr<Flightcontroller> GetInstance();

    bool Begin();
    void Update();
    void CheckFailsafe();
    void Disarm();


    
    
private:
    Flightcontroller();

    std::shared_ptr<SensorManager> m_sensors;
    std::shared_ptr<Logger> m_logger;
    std::shared_ptr<ConfigManager> m_config;
    std::shared_ptr<RemoteControlHandler> m_remoteControl;
    std::shared_ptr<ActuatorManager> m_actuator;

    bool m_armed;
    bool m_failsafe;
    int m_rollCH;

    float calculateCorrection(float gyroValue, float remoteValue);

};

}
