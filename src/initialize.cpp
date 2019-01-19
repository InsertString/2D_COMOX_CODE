#include "main.h"

#define LEFT_FRONT_MOTOR 16
#define LEFT_BACK_MOTOR 15
#define RIGHT_FRONT_MOTOR 18
#define RIGHT_BACK_MOTOR 14
#define CATAPULT_MOTOR 11
#define INTAKE_MOTOR 20
#define CHAINBAR_MOTOR 13
#define FLIPPER_MOTOR 12
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

pros::Motor cat(CATAPULT_MOTOR);
pros::Motor intake(INTAKE_MOTOR);
pros::ADIAnalogIn cat_pot(D);

pros::Motor flipper(FLIPPER_MOTOR);
pros::Motor cBar(CHAINBAR_MOTOR);

Ball_System ball_system;
Lift_Systems lift;
Chassis chassis;


void initialize() {
	pros::lcd::initialize();
	cat.set_brake_mode(MOTOR_BRAKE_COAST);
	intake.set_brake_mode(MOTOR_BRAKE_COAST);

	//drive_RF.set_brake_mode(MOTOR_BRAKE_BRAKE);
	//drive_LF.set_brake_mode(MOTOR_BRAKE_BRAKE);
	drive_RB.set_brake_mode(MOTOR_BRAKE_BRAKE);
	drive_LB.set_brake_mode(MOTOR_BRAKE_BRAKE);

	flipper.set_brake_mode(MOTOR_BRAKE_BRAKE);
	cBar.set_brake_mode(MOTOR_BRAKE_BRAKE);
	selected_auto = 0;
	reset_auto_variables();
}

void disabled() {}

void competition_initialize() {}
