#include "MazeSolver.h"
#include "Sensors.h"
#include "Control.h"
/*
void MazeSolver::runLeftWallOnce() {
  bool left  = Sensors::wallLeft();
  bool right = Sensors::wallRight();
  float front = Sensors::frontDistanceCm();

  // Left-wall-follow rule set:
  if (!left) {
    Control::turnLeft90();
    Control::moveOneCell();
  } else if (front >= FRONT_STOP_DIST_CM) {
    Control::moveOneCell();
  } else if (!right) {
    Control::turnRight90();
    Control::moveOneCell();
  } else {
    // dead-end -> U-turn
    Control::turnRight90();
    Control::turnRight90();
    Control::moveOneCell();
  }
} 
*/