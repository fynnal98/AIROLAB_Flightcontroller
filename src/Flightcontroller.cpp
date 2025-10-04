#include "Flightcontroller.h"

namespace flightcontroller{

Flightcontroller::Flightcontroller()
    : m_sensors(SensorManager::GetInstance()),
      m_logger(Logger::GetInstance()),
      m_config(ConfigManager::GetInstance()),
      m_remoteControl(RemoteControlHandler::GetInstance()),
      m_actuator(ActuatorManager::GetInstance()),
      m_armed(false),
      m_failsafe(false),
      m_rollCH(-1)
{}
    
std::shared_ptr<Flightcontroller> Flightcontroller::GetInstance(){
    static std::shared_ptr<Flightcontroller> instance = nullptr;
    if (!instance){
        instance = std::shared_ptr<Flightcontroller>(new Flightcontroller());
    }
    return instance;
}

bool Flightcontroller::Begin(){
    int sda = ConfigManager::GetInstance()->Get<int>("sensors/settings/sda");
    int scl = ConfigManager::GetInstance()->Get<int>("sensors/settings/scl");
    float seaLevel = ConfigManager::GetInstance()->Get<float>("sensors/settings/seaLevel");

    //Sensor init
    if(!m_sensors->Begin(sda, scl, seaLevel)){
        LOG_ERROR("Sensor Init failed!");
        return false;
    }

    //Config init
    int sbus_rx = ConfigManager::GetInstance()->Get<int>("sbus/settings/rx");
    if(!m_remoteControl->Begin(sbus_rx)){
        LOG_ERROR("SBUS Init Failed");
        return false;
    }

    m_rollCH = ConfigManager::GetInstance()->Get<int>("sbus/assign/roll");

    return true;


}

// bool CheckSafetyHandler(){

// }

float Flightcontroller::calculateCorrection(float gyroValue, float remoteValue){
    float result = remoteValue - gyroValue;
    return result;
}

void Flightcontroller::Update(){
    m_sensors->Update();
    m_remoteControl->Update();
    
    float gyroX = m_sensors->GetMPU()->GetGyroX();
    float remoteX = m_remoteControl->GetChannelNorm(m_rollCH);
    float rollCorrection = calculateCorrection(gyroX, remoteX);
    m_actuator->SetRoll(rollCorrection);
    LOG_DEBUG("ROLL: " + String(rollCorrection) + " Remote: " + String(remoteX));
}
}