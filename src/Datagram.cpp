#include "Datagram.h"

namespace flightcontroller
{

    uint8_t Datagram::s_msgId = 0;

    std::shared_ptr<Datagram> Datagram::GetInstance(){
        static std::shared_ptr<Datagram> instance = nullptr;
        if(!instance){
            instance = std::shared_ptr<Datagram>(new Datagram());
        }
        return instance;
    }

    std::vector<uint8_t> Datagram::CreateTelemetryDatagram(const MPUAccelleration& accelleration, const MPUGyro& gyro, const BMPData& bmpData)
    {
        std::vector<uint8_t> datagram;
        datagram.push_back(START_BYTE);
        datagram.push_back(s_msgId++);

        appendInt16(datagram, accelleration.x);
        appendInt16(datagram, accelleration.y);
        appendInt16(datagram, accelleration.z);

        appendInt16(datagram, gyro.x);
        appendInt16(datagram, gyro.y);
        appendInt16(datagram, gyro.z);

        appendFloat(datagram, bmpData.pressure);
        appendFloat(datagram, bmpData.temp);
        appendFloat(datagram, bmpData.altitude);

        appendChecksum(datagram);
        datagram.push_back(END_BYTE);

        return datagram;
    }

    /// @brief Appends the given float to the given datagram
    /// @param datagram The datagram the float shall be appended
    /// @param data The float to append
    void Datagram::appendFloat(std::vector<uint8_t>& datagram, float data)
    {
        uint8_t bytes[sizeof(float)];
        std::memcpy(bytes, &data, sizeof(float));
        datagram.insert(datagram.end(), bytes, bytes + sizeof(float));
    }

    void Datagram::appendInt16(std::vector<uint8_t>& datagram, uint16_t data)
    {
        datagram.push_back(static_cast<uint8_t>(data & 0xFF));
        datagram.push_back(static_cast<uint8_t>((data >> 8) & 0xFF));
    }
 
    void Datagram::appendChecksum(std::vector<uint8_t> datagram)
    {
        uint32_t crc = 0xFFFFFFFF; 
        for (uint8_t byte : datagram) {
            crc ^= byte;
            for (int i = 0; i < 8; ++i) {
                if (crc & 1)
                    crc = (crc >> 1) ^ 0xEDB88320;
                else
                    crc >>= 1;
            }
        }
        crc ^= 0xFFFFFFFF;
        
        datagram.push_back(static_cast<uint8_t>(crc & 0xFF));
        datagram.push_back(static_cast<uint8_t>((crc >> 8) & 0xFF));
        datagram.push_back(static_cast<uint8_t>((crc >> 16) & 0xFF));
        datagram.push_back(static_cast<uint8_t>((crc >> 24) & 0xFF));

    }

}