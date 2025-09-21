#include "InputManager.h"
#include "Logger.h"

namespace flightcontroller{

InputManager::InputManager() : m_sbus(nullptr) {}

InputManager& InputManager::getInstance(){
    static InputManager instance;
    return instance;
}

void InputManager::begin(int rxPin) {
    m_sbus = new bfs::SbusRx(&Serial2, rxPin, -1, true);
    m_sbus->Begin();
    LOG_INFO("SBUS gestartet");
}


void InputManager::update() {
    if (m_sbus && m_sbus->Read()) {
        auto data = m_sbus->data();
        receivedData.clear();

        for (int i = 0; i < bfs::SbusData::NUM_CH; ++i) {
            channelData[i] = data.ch[i];
            receivedData += String(channelData[i]) + ",";
        }
    }
}

int16_t InputManager::getChannelRaw(int ch) const {
    if (ch < 1 || ch > bfs::SbusData::NUM_CH) 
        return -1;
    return channelData[ch - 1];
}

float InputManager::getChannelNorm(int ch) const {
    if (ch < 1 || ch > bfs::SbusData::NUM_CH) 
        return 0.0f;

    float result = map(channelData[ch - 1], 172, 1811, -1000, 1000) / 1000.0f;
    return result;
}


}