#include "main.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

	while (true) {
		drive_LF = -master.get_analog(ANALOG_LEFT_Y);
		drive_LB = master.get_analog(ANALOG_LEFT_Y);
		drive_RF = master.get_analog(ANALOG_RIGHT_Y);
		drive_RB = -master.get_analog(ANALOG_RIGHT_Y);

		if (master.get_digital(DIGITAL_L1)) {
			intake = 127;
		}
		else if (master.get_digital(DIGITAL_L2)) {
			intake = -127;
		}
		else
			intake = 0;



		if (master.get_digital(DIGITAL_R1) && cat_down.get_value() == false) {
			cat = -127;
		}
		else if (cat_down.get_value() == true && master.get_digital(DIGITAL_R1)) {
			cat = 0;
		}
		else if (cat_down.get_value() == true && master.get_digital(DIGITAL_R2) == 0) {
			cat = -127;
		}
		else {
			cat = 0;
		}

		/*
		if (master.get_digital(DIGITAL_R1) && cat_down.get_value() == true) {
			cat = -127;
		}
		else if (cat_down.get_value() == true) {
			cat = 0;
		}
		else {
			cat = -127;
		}

		*/

		pros::delay(20);
	}
}
