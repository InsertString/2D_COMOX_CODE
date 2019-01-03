#include "main.h"

void opcontrol() {
	int i;
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
			cat = -10;
		}
		else if (cat_down.get_value() == true && master.get_digital(DIGITAL_R2) == 0) {
			cat = -127;
		}
		else {
			cat = 0;
		}

		pros::delay(20);
	}
}
