#include "main.h"
#include "robot_includes/robot_includes.h"




int auto_step;

Auto_Function a;
Auto_Function b;
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
  a = b = c = INCOMPLETE;
}





void flag_auto(int colour) {
  switch (auto_step) {
    case 0 :
    ball_system.setIntakePower(127);
    lift.setFlipperPower(3);
    a = chassis.PID_drive(3000, 100);
    if (a == COMPLETE || getTime(AUTO_STEP_TIMEOUT) > 2000) {
      advance_auto_step();
    }
    break;
    case 1 :
    if (getTime(AUTO_STEP_TIMEOUT) > 500) {
      ball_system.setIntakePower(50);
      a = chassis.PID_drive(-3000, 100);
      if (a == COMPLETE || getTime(AUTO_STEP_TIMEOUT) > 3000) {
        advance_auto_step();
      }
    }
    break;
    case 2 :
    a = chassis.PID_turn(900, 100);
    if (a == COMPLETE) b = ball_system.shoot();
    if ((a == COMPLETE && b == COMPLETE) || getTime(AUTO_STEP_TIMEOUT)) {
      advance_auto_step();
    }
    break;
    case 3 :
    a = chassis.PID_turn(1800, 127);
    if (a == COMPLETE || getTime(3000)) {
      ball_system.setIntakePower(127);
      advance_auto_step();
    }
    break;
    case 4 :
    a = chassis.PID_drive(3000, 100);
    break;
  }
}
