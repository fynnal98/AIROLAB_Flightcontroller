#pragma once
#include <Arduino.h>
#include <Adafruit_BMP280.h> 
#include <memory>

namespace flightcontroller {

class BMP280Handler {
public:
    static std::shared_ptr<BMP280Handler> GetInstance();
    bool begin(int sdaPin, int sclPin, float seaLevelhPa);
    void update(); 

    float GetPressure() const{
        return m_pressure;
    }
    float GetTemperature() const{
        return m_temperature;
    }
    float GetAltitude() const{
        return m_altitude;
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
