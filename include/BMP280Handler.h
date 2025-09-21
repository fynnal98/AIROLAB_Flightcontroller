#pragma once
#include <Arduino.h>
#include <Adafruit_BMP280.h> 

namespace flightcontroller {

class BMP280Handler {
public:
    static BMP280Handler& getInstance();
    bool begin(int sdaPin, int sclPin);
    void update(float seaLevelhPa); 

    float getPressure() const{
        return m_pressure;
    }
    float getTemperature() const{
        return m_temperature;
    }
    float getAltitude() const{
        return m_altitude;
    }


private:
    BMP280Handler();

    Adafruit_BMP280 m_bmp;
   
    float m_pressure;
    float m_temperature;
    float m_altitude;
};
}
