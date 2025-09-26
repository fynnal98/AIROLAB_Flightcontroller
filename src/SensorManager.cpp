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

bool SensorManager::begin(int sda, int scl, float seaLevelhPa){
    if (!m_mpu->begin(sda, scl)) {
        LOG_ERROR("MPU6050 init failed!");
        return false;
    }

    if (!m_bmp->begin(sda, scl, seaLevelhPa)) {
        LOG_ERROR("BMP280 init failed!");
        return false;
    }

    LOG_INFO("All Sensors initialized");

    return true;

}
void SensorManager::update(){
    m_mpu->update();
    m_bmp->update();
}
}