#include "OutputManager.h"

namespace flightcontroller
{ 
    /// @brief Constructor for the OutputManger
    /// @param port The port on which the socket will be opened
    OutputManager::OutputManager(uint16_t port) : m_port(port)
    {
        m_socket.begin(port);
    }

    /// @brief Destructor for the OutputManager
    /// @details Closes the UDP socket opened by the Constructor
    OutputManager::~OutputManager()
    {
        m_socket.stop();
    }

    /// @brief Send data to telemetry
    /// @param ip The IPv4 Address to send data to
    /// @param port The port to send data to
    /// @param data The data to send
    void OutputManager::SendData(const String& ip, uint16_t port, const std::vector<uint8_t>& data)
    {
        // IPAddress targetIp(ip.c_str());
        IPAddress targetIp;
        targetIp.fromString(ip);

        m_socket.beginPacket(targetIp, port);
        m_socket.write(data.data(), data.size());
        m_socket.endPacket();
    }
}