#pragma once
#include <Arduino.h>
#include <memory> 
#include <sbus.h>

namespace flightcontroller{

class RemoteControlHandler {
public: 
    static std::shared_ptr<RemoteControlHandler> GetInstance();

    bool Begin(int rxPin);
    void Update();

    int16_t GetChannelRaw(int ch) const;
    float GetChannelNorm(int ch) const;
    float GetByName(const String& name) const;


private:
    RemoteControlHandler();
    RemoteControlHandler(const RemoteControlHandler&) = delete;
    RemoteControlHandler& operator = (const RemoteControlHandler&) = delete;

    bfs::SbusRx* m_sbus;
    bfs::SbusData m_data;
    int16_t m_channels[16];

    float m_roll;
    float m_pitch;
    float m_yaw;
    float m_throttle;

    int16_t channelData[bfs::SbusData::NUM_CH] = {0};
    String receivedData;

};
}