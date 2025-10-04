#pragma once

#include "Constants.h"
#include "Types.h"

#include <cstdint>
#include <cstring>
#include <memory>
#include <vector>

namespace flightcontroller
{
    /// @brief The datagram class
    /// @details This class contains functions for constructing datagrams to transmit telemetry data.
    ///          The format of the datagram is as follows:
    ///          START_BYTE (1 Byte) | MSG_ID (1 Byte) |
    ///          MPUAccX (4 Bytes) | MPUAccY (4 Bytes) | MPUAccZ (4 Bytes) | 
    ///          MPUGyroX (4 Bytes) | MPUGyroY (4 Bytes) | MPUGyroZ (4 Bytes) | 
    ///          BMPPressure (4 Bytes) | BMPTemp (4 Bytes) | BMPAltitude (4 Bytes) | 
    ///          CRC32_CHECKSUM (4 Bytes) | END_BYTE (1 Byte)
    class Datagram
    {
    public:
        static std::shared_ptr<Datagram> GetInstance();
    
        Datagram(const Datagram&) = delete;
        Datagram& operator = (const Datagram&) = delete;
        
        ~Datagram() = default;

        std::vector<uint8_t> CreateTelemetryDatagram(const MPUAccelleration& accelleration, const MPUGyro& gyro, const BMPData& bmpData);

    private:
        Datagram() = default;
        
        void appendFloat(std::vector<uint8_t>& datagram, float data);
        void appendInt16(std::vector<uint8_t>& datagram, uint16_t data);

        void appendChecksum(std::vector<uint8_t> datagram);

        static uint8_t s_msgId; 
    };
}