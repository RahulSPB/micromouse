#include "Control.h"
#include "Motors.h"
#include "Encoders.h"
#include "Sensors.h"

static PID pidDist(KP_DIST, KI_DIST, KD_DIST);
static PID pidHead(KP_HEAD, KI_HEAD, KD_HEAD);
static PID pidTurn(KP_TURN, KI_TURN, KD_TURN);

float Control::readHeading() {
  mpu.update();
  return mpu.getAngleZ();
}

void Control::init() {
  // Nothing extra for now
}

void Control::moveOneCell() {
  Serial.println("[CTRL] Move 1 cell");
  Encoders::reset();
  pidDist.reset();
  pidHead.reset();
  // Heading reference
  float head0 = readHeading();
  long target = (long)PULSES_PER_CELL;

  while (true) {
    long l = Encoders::left();
    long r = Encoders::right();
    long avg = (l + r) / 2;

    if (Sensors::frontDistanceCm() < FRONT_STOP_DIST_CM) {
      Serial.println("[CTRL] Front wall: stopping early");
      break;
    }
    if (avg >= target) {
      Serial.println("[CTRL] Target pulses reached");
      break;
    }

    float head = readHeading();
    float corr = pidHead.compute(head0, head); // (+) if we veer right
    corr = constrain(corr, -MAX_CORR_PWM, MAX_CORR_PWM);

    float distOut = pidDist.compute(target, avg);
    int base = constrain((int)distOut, -FWD_SPEED_PWM, FWD_SPEED_PWM);

    int leftPWM  = constrain(base - (int)corr, -PWM_MAX, PWM_MAX);
    int rightPWM = constrain(base + (int)corr, -PWM_MAX, PWM_MAX);

    Motors::setLeft(leftPWM);
    Motors::setRight(rightPWM);
    delay(5);
  }
  Motors::brake();
}

void Control::turnLeft90() {
  Serial.println("[CTRL] Turn LEFT 90");
  pidTurn.reset();
  float start = readHeading();
  float goal  = start - 90.0f;

  while (true) {
    float ang = readHeading();
    float out = pidTurn.compute(goal, ang);
    int sp = constrain((int)abs(out), 0, TURN_SPEED_PWM);
    Motors::setLeft(-sp);
    Motors::setRight(+sp);
    if (abs(ang - goal) < 1.0f) break;
    delay(5);
  }
  Motors::brake();
}

void Control::turnRight90() {
  Serial.println("[CTRL] Turn RIGHT 90");
  pidTurn.reset();
  float start = readHeading();
  float goal  = start + 90.0f;

  while (true) {
    float ang = readHeading();
    float out = pidTurn.compute(goal, ang);
    int sp = constrain((int)abs(out), 0, TURN_SPEED_PWM);
    Motors::setLeft(+sp);
    Motors::setRight(-sp);
    if (abs(ang - goal) < 1.0f) break;
    delay(5);
  }
  Motors::brake();
}
