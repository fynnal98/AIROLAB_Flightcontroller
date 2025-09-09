# AIRLAB Flightcontroller

## Struktur

- src/ – Firmware-Code für den Flightcontroller  
- extern/DatabaseManager/ – C++ Bibliothek zur Arbeit mit der Datenbank  
- extern/Database/ – Enthält die database.json (als Submodul)  
- data/ – wird beim UploadFS auf den ESP32 geschrieben  
- tools/ – Hilfsskripte (run.bat, monitor.bat, …)

## Klassendiagramm

```mermaid
classDiagram
    direction LR

    class FlightController {
        +setup()
        +loop()
        -DatabaseManager db
    }

    class DatabaseManager {
        +bool load(path)
        +String get(path)
        +bool set(path, value)
        +String exportJson()
    }

    class Sensors {
        +update()
    }

    class Actuators {
        +write()
    }

    class Telemetry {
        +send()
        +receive()
    }

    FlightController --> DatabaseManager : nutzt
    FlightController --> Sensors
    FlightController --> Actuators
    FlightController --> Telemetry
