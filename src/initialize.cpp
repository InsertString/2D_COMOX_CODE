




#include "main.h"

#define LEFT_FRONT_MOTOR 16
#define LEFT_BACK_MOTOR 15
#define RIGHT_FRONT_MOTOR 18
#define RIGHT_BACK_MOTOR 14
#define A 1
#define B 2
#define C 3
#define D 4
#define E 5

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor drive_LF(LEFT_FRONT_MOTOR);
pros::Motor drive_RF(RIGHT_FRONT_MOTOR);
pros::Motor drive_LB(LEFT_BACK_MOTOR);
pros::Motor drive_RB(RIGHT_BACK_MOTOR);
pros::ADIGyro gyro(C);

pros::Motor cat(11);
pros::Motor intake(20);
pros::ADIAnalogIn cat_pot(D);

pros::Motor cap_scorer(13);

Ball_System ball_system;


void initialize() {
	pros::lcd::initialize();
	cat.set_brake_mode(MOTOR_BRAKE_BRAKE);
	intake.set_brake_mode(MOTOR_BRAKE_COAST);
}

void disabled() {}

void competition_initialize() {}
