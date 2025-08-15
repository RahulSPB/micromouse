#ifndef PID_H
#define PID_H
#include <Arduino.h>

class PID {
public:
  PID(float kp, float ki, float kd);
  void reset();
  float compute(float setpoint, float measure);

private:
  float kp, ki, kd;
  float integ, prevErr;
  unsigned long lastMs;
};

#endif
