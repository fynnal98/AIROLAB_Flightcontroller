#include "SensorManager.h"

namespace flightcontroller {

SensorManager::SensorManager()
    : m_mpu(MPU6050Handler::GetInstance()), 
    m_bmp(BMP280Handler::GetInstance()) 
    {}

std::shared_ptr<SensorManager> SensorManager::GetInstance() {
    static std::shared_ptr<SensorManager> instance = nullptr;
    if (!instance)
        instance = std::shared_ptr<SensorManager>(new SensorManager());
    return instance;
}

bool SensorManager::Begin(int sda, int scl, float seaLevelhPa){
    if (!m_mpu->Begin(sda, scl)) {
        LOG_ERROR("MPU6050 init failed!");
        return false;
    }
    if (!m_bmp->Begin(sda, scl, seaLevelhPa)) {
        LOG_ERROR("BMP280 init failed!");
        return false;
    }

    return true;

}
void SensorManager::Update(){
    m_mpu->Update();
    m_bmp->Update();
}
}