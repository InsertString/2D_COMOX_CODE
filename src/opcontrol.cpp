#include "main.h"

void opcontrol() {
	int l = -1;
	int r = 1;
	while (true) {
		drive_RF = master.get_analog(ANALOG_LEFT_Y) * r;
		drive_RB = master.get_analog(ANALOG_LEFT_Y) * r;
		drive_LF = master.get_analog(ANALOG_RIGHT_Y) * l;
		drive_LB = master.get_analog(ANALOG_RIGHT_Y) * l;

		if (master.get_digital_new_press(DIGITAL_Y)) {
			l *= -1;
			r *= -1;
		}

		ball_system.drive();

		pros::lcd::print(0, "cat_pot %d", cat_pot.get_value());
		pros::lcd::print(1, "cat temp : %f", cat.get_temperature());

		pros::delay(20);
	}
}
