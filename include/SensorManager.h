#pragma once
#include <memory>
#include "MPU6050Handler.h"
#include "BMP280Handler.h"
#include "Logger.h"

namespace flightcontroller {
class SensorManager {
public:
    static  std::shared_ptr<SensorManager> GetInstance();

    bool Begin(int sda, int scl, float seaLevelhPa);
    void Update();
    
    std::shared_ptr<MPU6050Handler> GetMPU() const { 
        return m_mpu; 
    }
    std::shared_ptr<BMP280Handler> GetBMP() const { 
        return m_bmp; 
    }

private:
    SensorManager();
    SensorManager(const SensorManager&) = delete;
    SensorManager& operator=(const SensorManager&) = delete;

    std::shared_ptr<MPU6050Handler> m_mpu;
    std::shared_ptr<BMP280Handler> m_bmp;

};
}

