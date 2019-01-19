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
  drive_pid.set_Constants(0.19, 1, 2);
  turn_pid.set_Constants(0.15, 1, 15);
  drive_step = 0;
  turn_step = 0;
}



void Chassis::reset_drive_sensors(bool reset_gyro) {
  if (reset_gyro == true) {
    gyro.reset();
  }

  drive_RF.tare_position();
  drive_LF.tare_position();
}



void Chassis::reset_chassis_auto_vars() {
	reset_drive_sensors(false);
	drive_step = 0;
  turn_step = 0;
}



void Chassis::setLeftPower(int power) {
  drive_LB = -power;
  drive_LF = -power;
}



void Chassis::setRightPower(int power) {
  drive_RB = power;
  drive_RF = power;
}





int Chassis::left_pos() {
  return drive_LF.get_position();
}




int Chassis::right_pos() {
  return drive_RF.get_position();
}





Auto_Function Chassis::PID_drive(int target, int max_power) {
  Auto_Function return_state = INCOMPLETE;

  switch(drive_step) {
    case 0 :
    //set default values//
    reset_drive_sensors(true);
    drive_pid.set_pid_vars(target, 15, true, 9);
    gyro_error = 0;
    return_state = INCOMPLETE;
    //reset timers//
    resetTimer(DRIVE_PID_EXIT);
    resetTimer(DRIVE_PID_TIMEOUT);
    //increase step//
    drive_step++;
    break;
    case 1 :
    //set gyro error
    gyro_error = 0 - gyro.get_value();

    int out_L;
    int out_R;

    out_L = drive_pid.output(right_pos(), max_power) - (gyro_error * 0.5);
    out_R = drive_pid.output(right_pos(), max_power) + (gyro_error * 0.5);

    setLeftPower(out_L);
    setRightPower(out_R);

    if (abs(drive_pid.error) < 100 || getTime(DRIVE_PID_TIMEOUT) > 2000) {
      if (getTime(DRIVE_PID_EXIT) > 50) drive_step++;
    }
    else
      resetTimer(DRIVE_PID_EXIT);

    break;
    case 2 :
    setLeftPower(0);
    setRightPower(0);
		return_state = COMPLETE;
    break;
  }

  return return_state;
}





Auto_Function Chassis::PID_turn(int target, int max_power) {
  Auto_Function return_state = INCOMPLETE;

  switch(turn_step) {
    case 0 :
    //set default values//
    reset_drive_sensors(true);
    turn_pid.set_pid_vars(target, 11, true, 5);
    return_state = INCOMPLETE;
    //reset timers/
    resetTimer(TURN_PID_EXIT);
    resetTimer(TURN_PID_TIMEOUT);
    //increase step//
    turn_step++;
    break;
    case 1 :
    int out_L;
    int out_R;

    out_L = -turn_pid.output(gyro.get_value(), max_power);
    out_R = turn_pid.output(gyro.get_value(), max_power);

    setLeftPower(out_L);
    setRightPower(out_R);

    if (abs(turn_pid.error) < 10 || getTime(TURN_PID_TIMEOUT) > 2000) {
      if (getTime(DRIVE_PID_EXIT) > 50) turn_step++;
    }
    else
      resetTimer(TURN_PID_EXIT);

    break;
    case 2 :
    setLeftPower(0);
    setRightPower(0);
		return_state = COMPLETE;
    break;
  }

  return return_state;
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
