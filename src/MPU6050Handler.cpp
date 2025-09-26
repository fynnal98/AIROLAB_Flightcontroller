#include "MPU6050Handler.h"

namespace flightcontroller {


MPU6050Handler::MPU6050Handler()
    : m_accelX(0), m_accelY(0), m_accelZ(0),
      m_gyroX(0), m_gyroY(0), m_gyroZ(0), m_tempRaw(0) {}


std::shared_ptr<MPU6050Handler> MPU6050Handler::GetInstance() {
    static std::shared_ptr<MPU6050Handler> instance = nullptr;
    if (!instance)
        instance = std::shared_ptr<MPU6050Handler>(new MPU6050Handler());
    return instance;
}


bool MPU6050Handler::begin(int sdaPin, int sclPin) {
    if(!Wire.begin(sdaPin, sclPin)){
        LOG_ERROR("I2C init failed!");
        return false;
    }
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(REG_PWR_MGMT_1);
    Wire.write(0);
    if (Wire.endTransmission() != 0) {
        LOG_ERROR("MPU6050 not found!");
        return false;
    }

    LOG_INFO("MPU6050 initialized");
    return true;
}

void MPU6050Handler::update() {
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(REG_ACCEL_XOUT_H);
    Wire.endTransmission(false);

    Wire.requestFrom(MPU6050_ADDR, (uint8_t)14);

    m_accelX = (Wire.read() << 8) | Wire.read();
    m_accelY = (Wire.read() << 8) | Wire.read();
    m_accelZ = (Wire.read() << 8) | Wire.read();

    m_tempRaw = (Wire.read() << 8) | Wire.read();

    m_gyroX = (Wire.read() << 8) | Wire.read();
    m_gyroY = (Wire.read() << 8) | Wire.read();
    m_gyroZ = (Wire.read() << 8) | Wire.read();
}

}