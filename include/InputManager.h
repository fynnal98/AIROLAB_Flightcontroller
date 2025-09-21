#pragma once 
#include "sbus.h"

namespace flightcontroller{

class InputManager {
public: 
    static InputManager& getInstance();

    void begin(int rxPin);
    void update();

    int16_t getChannelRaw(int ch) const;
    float getChannelNorm(int ch) const;
    float getByName(const String& name) const;


private:
    InputManager();
    InputManager(const InputManager&) = delete;
    InputManager& operator = (const InputManager&) = delete;

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