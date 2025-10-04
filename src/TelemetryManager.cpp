    #include "TelemetryManager.h"
    #include "SensorManager.h"

    namespace flightcontroller
    {

        std::shared_ptr<TelemetryManager> TelemetryManager::GetInstance()
        {
            static std::shared_ptr<TelemetryManager> instance = nullptr; 
            if(!instance){
                instance = std::shared_ptr<TelemetryManager>(new TelemetryManager());
            }
            return instance;
        }

        TelemetryManager::TelemetryManager()
        {
            auto config = ConfigManager::GetInstance();
            int txPort = config->Get<int>("wifi/tx-port");
            m_pOutputManager = std::make_shared<OutputManager>(txPort);

            m_pDatagram = Datagram::GetInstance();
            m_pSensorManager = SensorManager::GetInstance();
        }

        void TelemetryManager::SendTelemetryData()
        {
            MPUAccelleration accelleration = m_pSensorManager->GetMPU()->GetAccelleration();
            MPUGyro gyro = m_pSensorManager->GetMPU()->GetGyro();
            BMPData bmpData = m_pSensorManager->GetBMP()->GetSensorData();

            std::vector<uint8_t> datagram = m_pDatagram->CreateTelemetryDatagram(accelleration, gyro, bmpData);
            
            m_pOutputManager->SendData("192.168.4.10", 4000, datagram);

        }

    }
