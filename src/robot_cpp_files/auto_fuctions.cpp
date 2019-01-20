#include "main.h"
#include "robot_includes/robot_includes.h"




int auto_step;

Auto_Function i;
Auto_Function f;
Auto_Function c;




void start_auto() {
  reset_auto_variables();
  auto_step = 0;
}




void reset_auto_variables() {
  chassis.reset_chassis_auto_vars();
  ball_system.shoot_step = 0;
  ball_system.pull_back_step = 0;
  resetTimer(AUTO_STEP_TIMEOUT);
}





void advance_auto_step() {
  auto_step++;
  reset_auto_variables();
  resetTimer(AUTO_STEP_TIMEOUT);
  i = f = c = INCOMPLETE;
}





void flag_auto(int colour) {
  switch (auto_step) {
    case 0 :
    ball_system.setIntakePower(127);
    lift.setFlipperPower(3);
    i = chassis.PID_drive(3000, 100);
    if (i == COMPLETE || getTime(AUTO_STEP_TIMEOUT) > 2000) {
      advance_auto_step();
    }
    break;
    case 1 :
    if (getTime(AUTO_STEP_TIMEOUT) > 500) {
      i = chassis.PID_drive(-2900, 100);
      if (i == COMPLETE || getTime(AUTO_STEP_TIMEOUT) > 3000) {
        advance_auto_step();
      }
    }
    break;
    case 2 :
    int a;
    if (colour == RED) {
      a = 880;
    }
    else if (colour == BLUE) {
      a = -880;
    }
    ball_system.setIntakePower(0);
    i = chassis.PID_turn(a, 100);
    if (i == COMPLETE) {
      advance_auto_step();
    }
    break;
    case 3 :
    f = chassis.PID_drive(-500, 70);
    if (f == COMPLETE) {
      i = ball_system.shoot();
      if (i == COMPLETE) {
        advance_auto_step();
      }
    }
    break;
    case 4 :
    if (colour == RED) {
      a = 1900;
    }
    else if (colour == BLUE) {
      a = -1900;
    }
    i = chassis.PID_turn(a, 127);
    ball_system.setIntakePower(127);
    if (i == COMPLETE) {
      advance_auto_step();
    }
    break;
    case 5 :
    i = chassis.PID_drive(3000, 100);
    break;
  }
}
