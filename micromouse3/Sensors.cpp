#include "Sensors.h"
#include <Arduino.h>
#include <math.h>

void Sensors::init() {
  pinMode(PIN_IR_LEFT, INPUT);
  pinMode(PIN_IR_RIGHT, INPUT);
  analogSetPinAttenuation(PIN_IR_FRONT, ADC_11db);
  analogReadResolution(12);
}

float Sensors::frontDistanceCm() {
  int raw = analogRead(PIN_IR_FRONT);
  float v = raw * (3.3f / 4095.0f);
  // Typical fit for GP2Y0A21 (tweak later with calibration)
  float cm = 27.86f * powf(v, -1.15f);
  return cm;
}

bool Sensors::wallLeft()  { return digitalRead(PIN_IR_LEFT)  == WALL_DETECTED; }
bool Sensors::wallRight() { return digitalRead(PIN_IR_RIGHT) == WALL_DETECTED; }
