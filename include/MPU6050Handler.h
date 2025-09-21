#pragma once 
#include <Arduino.h>
#include <Wire.h>
#include "Logger.h"

namespace flightcontroller{

class MPU6050Handler{
public:
    static MPU6050Handler& getInstance();

    static constexpr float TEMP_SCALE  = 340.0f;
    static constexpr float TEMP_OFFSET = 36.53f;
    float getTemperature() const {
        return (m_tempRaw / TEMP_SCALE) + TEMP_OFFSET;
    }
    
    bool begin(int sdaPin, int sclPin);
    void update();

    int16_t getAccelX() const {
        return m_accelX;
    }

    int16_t getAccelY() const {
        return m_accelY;
    }

    int16_t getAccelZ() const {
        return m_accelZ;
    }

    int16_t getGyroX() const {
        return m_gyroX;
    }

    int16_t getGyroY() const {
        return m_gyroY;
    }

    int16_t getGyroZ() const {
        return m_gyroZ;
    }

private:
    MPU6050Handler();
    // I2C-Adresse des Sensors
    static constexpr uint8_t MPU6050_ADDR = 0x68;

    // Register
    static constexpr uint8_t REG_PWR_MGMT_1 = 0x6B;
    static constexpr uint8_t REG_ACCEL_XOUT_H = 0x3B;

    // Daten
    int16_t m_accelX, m_accelY, m_accelZ;
    int16_t m_gyroX, m_gyroY, m_gyroZ;
    int16_t m_tempRaw;

    // Hilfsfunktion: Register lesen
    int16_t read16Bit(uint8_t reg);
};
}