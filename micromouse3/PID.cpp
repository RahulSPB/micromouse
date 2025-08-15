#include "PID.h"

PID::PID(float p, float i, float d)
: kp(p), ki(i), kd(d), integ(0), prevErr(0), lastMs(0) {}

void PID::reset() {
  integ = 0; prevErr = 0; lastMs = 0;
}

float PID::compute(float set, float mea) {
  unsigned long now = millis();
  float dt = (lastMs==0) ? 0.0f : (now - lastMs) / 1000.0f;
  float err = set - mea;
  integ += err * dt;
  float deriv = (lastMs==0) ? 0.0f : (err - prevErr) / dt;
  float out = kp*err + ki*integ + kd*deriv;
  prevErr = err; lastMs = now;
  return out;
}
