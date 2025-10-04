#pragma once 
#include <Arduino.h>

namespace flightcontroller {

class PID {

public: 
    PID(float kp, float ki, float kd);
    float Update(float setpoint, float measured, float dt);

private:
    float m_kp;
    float m_ki;
    float m_kd;

    float m_prevError;
    float m_integral;


};

}