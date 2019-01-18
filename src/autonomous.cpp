#include "main.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  resetTimer(AUTO_TIMER);
  chassis.reset_chassis_auto_vars();
  while (getTime(AUTO_TIMER) < 15000) {
    //chassis.PID_drive(-1000, 100);
    chassis.PID_turn(-900, 100);
  }
}
