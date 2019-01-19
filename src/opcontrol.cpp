#include "main.h"

void opcontrol() {
	int l = -1;
	int r = 1;
	int direction = 0;
	cBar.tare_position();
	flipper.tare_position();
	int count = 0;
	int a = 1;

	while (true) {
		if (!(count % 2)) {
      if (lift.curr_system == 1 && a == 0) {
				master.print(0, 0, "SYSTEM : [CBAR]");
				a = 1;
			}
			else if (lift.curr_system == 2 && a == 1) {
				master.print(0, 0, "SYSTEM : [FLIP]");
				a = 0;
			}
    }
    count++;

		chassis.drive();

		lift.drive();

		ball_system.drive();

		lcd_control();
/*
		pros::lcd::print(0, "cat_pot %d", cat_pot.get_value());
		pros::lcd::print(1, "cat temp : %f", cat.get_temperature());
		pros::lcd::print(2, "cBar position : %d", cBar.get_position());
		pros::lcd::print(3, "flipper : %d", flipper.get_position());
		pros::lcd::print(4, "gyro val : %f", gyro.get_value());
		pros::lcd::print(5, "drive encoder value : %d", chassis.right_pos());
*/
		pros::delay(20);
	}
}
