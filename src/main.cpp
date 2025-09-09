#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("ESP32 is runnnning");

    if (!LittleFS.begin()) {
        Serial.println("LittleFS failed");
        return;
    }

    File f = LittleFS.open("/database.json", "r");
    if (!f) {
        Serial.println("database.json nicht gefunden!");
        return;
    }

    // JSON einlesen
    StaticJsonDocument<2048> doc;  // Größe noch anpassen
    DeserializationError err = deserializeJson(doc, f);
    f.close();

    if (err) {
        Serial.print("JSON Fehler: ");
        Serial.println(err.c_str());
        return;
    }

    const char* mode = doc["settings"]["system"]["mode"];
    int servo1 = doc["settings"]["hardware"]["servo_1"];
    float kp_roll = doc["settings"]["pid"]["roll"]["kp"];


    //DEBUG
    Serial.println("JSON geladen:");
    Serial.printf("  System-Mode: %s\n", mode);
    Serial.printf("  Servo 1 Pin: %d\n", servo1);
    Serial.printf("  Roll Kp: %.3f\n", kp_roll);
}

void loop() {
    delay(2000);
}
