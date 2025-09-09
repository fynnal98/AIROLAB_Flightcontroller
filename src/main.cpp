#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("🔄 ESP32 gestartet!");
  if (!LittleFS.begin()) {
    Serial.println("LittleFS mount failed!");
    return;
  }

  File f = LittleFS.open("/database.json", "r");
  if (!f) {
    Serial.println("database.json nicht gefunden!");
    return;
  }

  Serial.println("database.json geöffnet");
  while (f.available()) {
    Serial.write(f.read());  
  }
  f.close();
  Serial.println("\n--- ENDE DER DATEI ---");
}

void loop() {

}
