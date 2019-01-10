#include "main.h"

void opcontrol() {
	int i;
	while (true) {
		drive_RF = master.get_analog(ANALOG_LEFT_Y);
		drive_RB = master.get_analog(ANALOG_LEFT_Y);
		drive_LF = -master.get_analog(ANALOG_RIGHT_Y);
		drive_LB = -master.get_analog(ANALOG_RIGHT_Y);


		if (master.get_digital(DIGITAL_L1)) {
			intake = -127;
		}
		else if (master.get_digital(DIGITAL_L2)) {
			intake = 127;
		}
		else
			intake = 0;

		if (master.get_digital(DIGITAL_R1) && cat_pot.get_value() < 1450) {
			cat = -127;
		}
		else if (master.get_digital(DIGITAL_R1) && cat_pot.get_value() > 1450) {
			cat = -7;
		}
		else if (!master.get_digital(DIGITAL_R1) && cat_pot.get_value() > 1300) {
			cat = -127;
		}
		else {
			cat = 0;
		}


		//ball_system.drive();



		pros::lcd::print(0, "cat_pot %d\n", cat_pot.get_value());

		pros::delay(20);
	}
}
