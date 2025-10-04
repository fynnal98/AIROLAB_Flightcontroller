#include "ActuatorManager.h"

namespace flightcontroller{
    ActuatorManager::ActuatorManager(){}

    std::shared_ptr<ActuatorManager> ActuatorManager::GetInstance(){
        static std::shared_ptr<ActuatorManager> instance = nullptr;
        if (!instance){
            instance = std::shared_ptr<ActuatorManager>(new ActuatorManager);
        }
        return instance;
    }

    bool ActuatorManager::Begin() {

        int pinAileronRH = m_config->Get<int>("pin/control/control/aileronRH");
        int pinAileronLH = m_config->Get<int>("pin/control/control/aileronLH");
        int pinElevator = m_config->Get<int>("pin/control/control/elevator");
        m_servoRollRH.attach(pinAileronRH);
        m_servoRollLH.attach(pinAileronLH);
        m_servoPitch.attach(pinElevator);

        return true;
    }

    void ActuatorManager::SetRoll(float value){
        int pulse = map(value * 1000, -1000, 1000, 1000, 2000);
        // LOG_DEBUG("Aileron: " + pulse);
        // m_servoRollRH.writeMicroseconds(pulse);
        // m_servoRollLH.writeMicroseconds(-pulse);
    }
    void ActuatorManager::SetPitch(float value){
        int pulse = map(value * 1000, -1000, 1000, 1000, 2000);
        // LOG_DEBUG("Elevator: " + pulse);
        // m_servoPitch.writeMicroseconds(pulse);
    }
}