#include "RemoteControllHandler.h"
#include "Logger.h"

namespace flightcontroller{

RemoteControlHandler::RemoteControlHandler() : m_sbus(nullptr) {}

std::shared_ptr<RemoteControlHandler> RemoteControlHandler::GetInstance(){
    static std::shared_ptr<RemoteControlHandler> instance = nullptr;
    if(!instance){
        instance = std::shared_ptr<RemoteControlHandler>(new RemoteControlHandler());
    }
    return instance;
}

bool RemoteControlHandler::Begin(int rxPin) {
    Serial1.begin(100000, SERIAL_8E2, rxPin, -1); // RX = rxPin, TX = nicht benutzt
    m_sbus = new bfs::SbusRx(&Serial1, rxPin, -1, true);
    m_sbus->Begin();
    LOG_INFO("SBUS gestartet");
    return true;
    //TODO: LOGIK FÜR FAIL

}


void RemoteControlHandler::Update() {
    if (!m_sbus) {
        LOG_WARNING("SBUS Objekt fehlt");
        return;
    }
    if (m_sbus->Read()) {
        auto data = m_sbus->data();

        for (int i = 0; i < bfs::SbusData::NUM_CH; ++i) {
            channelData[i] = data.ch[i];
        }
        // LOG_DEBUG("SBUS Frame empfangen");
    } else {
        LOG_DEBUG("Kein SBUS Frame");
    }
}

int16_t RemoteControlHandler::GetChannelRaw(int ch) const {
    if (ch < 1 || ch > bfs::SbusData::NUM_CH) 
        return -1;
    return channelData[ch - 1];
}

float RemoteControlHandler::GetChannelNorm(int ch) const {
    if (ch < 1 || ch > bfs::SbusData::NUM_CH) 
        return 0.0f;

    float result = map(channelData[ch - 1], 172, 1811, -1000, 1000) / 1000.0f;

    return result;
}

}