#include "main.h"
#include "robot_includes/robot_includes.h"

#define INTAKE_FORWARD 1
#define CATAPULT_FORWARD 2

const unsigned int TrueSpeedArray[128] = {
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0, 0, 0, 0, 0, 22, 22, 23, 24, 24,
	25, 25, 25, 25, 26, 27, 27, 28, 28, 28,
	28, 29, 30, 30, 30, 31, 31, 32, 32, 32,
	33, 33, 34, 34, 35, 35, 35, 36, 36, 37,
	37, 37, 37, 38, 38, 39, 39, 39, 40, 40,
	41, 41, 42, 42, 43, 44, 44, 45, 45, 46,
	46, 47, 47, 48, 48, 49, 50, 50, 51, 52,
	52, 53, 54, 55, 56, 57, 57, 58, 59, 60,
	61, 62, 63, 64, 65, 66, 67, 67, 68, 70,
	71, 72, 72, 73, 74, 76, 77, 78, 79, 79,
	80, 81, 83, 84, 84, 86, 86, 87, 87, 88,
	88, 89, 89, 90, 90,127,127,127
};

Chassis::Chassis() {
  direction = INTAKE_FORWARD;
}



void Chassis::setLeftPower(int power) {
  drive_LB = -power;
  drive_LF = -power;
}



void Chassis::setRightPower(int power) {
  drive_RB = power;
  drive_RF = power;
}



void Chassis::drive() {
  int left;
  int right;

  if (master.get_digital_new_press(DIGITAL_Y)) {
    if (direction == INTAKE_FORWARD) {
      direction = CATAPULT_FORWARD;
    }
    else if (direction == CATAPULT_FORWARD) {
      direction = INTAKE_FORWARD;
    }
  }


  if (direction == INTAKE_FORWARD) {
    left = -master.get_analog(ANALOG_LEFT_Y) > 0 ? TrueSpeedArray[abs(master.get_analog(ANALOG_LEFT_Y))] : -TrueSpeedArray[abs(master.get_analog(ANALOG_LEFT_Y))];
    right = -master.get_analog(ANALOG_RIGHT_Y) > 0 ? TrueSpeedArray[abs(master.get_analog(ANALOG_RIGHT_Y))] : -TrueSpeedArray[abs(master.get_analog(ANALOG_RIGHT_Y))];
  }
  else if (direction == CATAPULT_FORWARD) {
    left = master.get_analog(ANALOG_RIGHT_Y) > 0 ? TrueSpeedArray[abs(master.get_analog(ANALOG_RIGHT_Y))] : -TrueSpeedArray[abs(master.get_analog(ANALOG_RIGHT_Y))];
    right = master.get_analog(ANALOG_LEFT_Y) > 0 ? TrueSpeedArray[abs(master.get_analog(ANALOG_LEFT_Y))] : -TrueSpeedArray[abs(master.get_analog(ANALOG_LEFT_Y))];
  }

  setLeftPower(left);
  setRightPower(right);

}
