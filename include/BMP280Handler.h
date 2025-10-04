#pragma once
#include "Types.h"

#include <Arduino.h>
#include <Adafruit_BMP280.h> 
#include <memory>

namespace flightcontroller {

class BMP280Handler {
public:
    static std::shared_ptr<BMP280Handler> GetInstance();
    bool Begin(int sdaPin, int sclPin, float seaLevelhPa);
    void Update(); 

    float GetPressure() const{
        return m_pressure;
    }
    float GetTemperature() const{
        return m_temperature;
    }
    float GetAltitude() const{
        return m_altitude;
    }

    BMPData GetSensorData() const{
        return BMPData(m_pressure, m_temperature, m_altitude);
    }

private:
    BMP280Handler();
    Adafruit_BMP280 m_bmp;
   
    float m_seaLevelhPa;
    float m_pressure;
    float m_temperature;
    float m_altitude;
};
}
