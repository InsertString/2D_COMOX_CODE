#include "main.h"

void opcontrol() {
	int l = -1;
	int r = 1;
	int direction = 0;
	while (true) {
		/*
		drive_RF = master.get_analog(ANALOG_LEFT_Y) * r;
		drive_RB = master.get_analog(ANALOG_LEFT_Y) * r;
		drive_LF = master.get_analog(ANALOG_RIGHT_Y) * l;
		drive_LB = master.get_analog(ANALOG_RIGHT_Y) * l;

		if (master.get_digital_new_press(DIGITAL_Y)) {
			l *= -1;
			r *= -1;
		}
		*/

		if (master.get_digital_new_press(DIGITAL_Y)) {
			if (direction == 1) {
				direction = 0;
			}
			else {
				direction = 1;
			}
		}

/*
		if (master.get_digital(DIGITAL_X)) {
			flipper = 127;
		}
		else if (master.get_digital(DIGITAL_B)) {
			flipper = -127;
		}
		else {
			flipper = 0;
		}

		if (master.get_digital(DIGITAL_UP)) {
			cBar = 127;
		}
		else if (master.get_digital(DIGITAL_DOWN)) {
			cBar = -127;
		}
		else {
			cBar = 0;
		}
*/

		lift.drive();

		if (direction == 1) {
			drive_RF = master.get_analog(ANALOG_LEFT_Y);
			drive_RB = master.get_analog(ANALOG_LEFT_Y);
			drive_LF = -master.get_analog(ANALOG_RIGHT_Y);
			drive_LB = -master.get_analog(ANALOG_RIGHT_Y);
		}
		else if (direction == 0) {
			drive_LF = master.get_analog(ANALOG_LEFT_Y);
			drive_LB = master.get_analog(ANALOG_LEFT_Y);
			drive_RF = -master.get_analog(ANALOG_RIGHT_Y);
			drive_RB = -master.get_analog(ANALOG_RIGHT_Y);
		}



		ball_system.drive();

		pros::lcd::print(0, "cat_pot %d", cat_pot.get_value());
		pros::lcd::print(1, "cat temp : %f", cat.get_temperature());

		pros::delay(20);
	}
}
