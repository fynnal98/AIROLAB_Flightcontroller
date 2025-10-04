#pragma once
#include <Arduino.h>
#include <cstdint>
#include <vector>
#include <WiFi.h>
#include <WiFiUdp.h>

#include "ConfigManager.h"

namespace flightcontroller{

    /// @brief The OutputManager class
    /// @details This class contains functions to send data using a UDP socket
    class OutputManager 
    {
    public:
        OutputManager(uint16_t port);
        ~OutputManager();

        void SendData(const String& ip, uint16_t port, const std::vector<uint8_t>& data);

    private:
        /// The UDP socket
        WiFiUDP m_socket;
        /// The local port
        uint16_t m_port;
    };

}