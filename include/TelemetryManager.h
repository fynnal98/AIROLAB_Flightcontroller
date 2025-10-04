#pragma once 
#include "ConfigManager.h"
#include "Datagram.h"
#include "OutputManager.h"
#include "SensorManager.h"
#include "Types.h"

#include <memory>
#include <vector>

namespace flightcontroller{
    class TelemetryManager
    {
    public:
        static std::shared_ptr<TelemetryManager>GetInstance();
        
        TelemetryManager(const TelemetryManager&) = delete;
        TelemetryManager& operator = (const TelemetryManager&) = delete;
        
        ~TelemetryManager() = default;

        void SendTelemetryData();

    private:
        TelemetryManager();

        std::shared_ptr<SensorManager> m_pSensorManager;
        std::shared_ptr<OutputManager> m_pOutputManager;
        std::shared_ptr<Datagram> m_pDatagram;
    };

}