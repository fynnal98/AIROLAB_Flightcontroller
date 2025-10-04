#include "PID.h"

namespace flightcontroller{

PID::PID(float kp, float ki, float kd) 
    : m_kp(kp), m_ki(ki), m_kd(kd),
      m_prevError(0), m_integral(0) {}


float PID::Update(float setpoint, float measured, float dt) {
    float error = setpoint - measured;
    m_integral += error * dt;
    float derivative = (error - m_prevError) / dt;
    m_prevError = error;
    return m_kp * error + m_ki * m_integral + m_kd * derivative;
}
}