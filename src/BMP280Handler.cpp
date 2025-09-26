#include "BMP280Handler.h"
#include "Logger.h"

namespace flightcontroller {

BMP280Handler::BMP280Handler()
    : m_temperature(0.0f), m_pressure(0.0f), m_altitude(0.0f) {}
  

std::shared_ptr<BMP280Handler> BMP280Handler::GetInstance() {
    static std::shared_ptr<BMP280Handler> instance = nullptr;
    if (!instance)
        instance = std::shared_ptr<BMP280Handler>(new BMP280Handler());
    return instance;
}

bool BMP280Handler::begin(int sdaPin, int sclPin, float seaLevelhPa) {
    m_seaLevelhPa = seaLevelhPa;
    if (!Wire.begin(sdaPin, sclPin)) {
        LOG_ERROR("I2C init failed!");
        return false;
    }
    if (!m_bmp.begin(0x76)) {
    LOG_ERROR("BMP280 not found!");
    return false;
    }

        // Sampling konfigurieren
    m_bmp.setSampling(
        Adafruit_BMP280::MODE_NORMAL,
        Adafruit_BMP280::SAMPLING_X2,   // Temp oversampling
        Adafruit_BMP280::SAMPLING_X16,  // Pressure oversampling
        Adafruit_BMP280::FILTER_X16,
        Adafruit_BMP280::STANDBY_MS_500
    );

    LOG_INFO("BMP280 initialized");
    return true;

}

void BMP280Handler::update() {
    m_temperature = m_bmp.readTemperature();
    m_pressure    = m_bmp.readPressure();                 // [Pa]
    m_altitude    = m_bmp.readAltitude(m_seaLevelhPa);      // [m]
}

}
