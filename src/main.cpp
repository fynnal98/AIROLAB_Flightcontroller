#include <Arduino.h>
#include "DatabaseManager.h"

DatabaseManager db;

void setup() {
    Serial.begin(115200);
    delay(500);

    Serial.println("Flightcontroller starting...");


    db.begin();
    db.load("/database.json");
    Serial.println("Database loaded.");

    float kp = db.getFloat("settings.pid.roll.kp");
    int servo1 = db.getInt("settings.hardware.servo_1");
    const char* mode = db.getString("settings.system.mode");

    Serial.printf("PID Roll Kp: %.2f\n", kp);
    Serial.printf("Servo 1: %d\n", servo1);
    Serial.printf("System Mode: %s\n", mode);

}

void loop() {
    delay(2000);
}
