




#include "main.h"


pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor drive_LF(16);
pros::Motor drive_RF(18);
pros::Motor drive_LB(17);
pros::Motor drive_RB(19);
pros::ADIGyro gyro(4);

pros::Motor fly_Top(11);
pros::Motor fly_Bot(12);
pros::Motor intake(20);

pros::Motor cap_scorer(13);


void initialize() {
	pros::lcd::initialize();
}

void disabled() {}

void competition_initialize() {}
