#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "sys/string.h"
#include "api.h"
#include "robot_includes/robot_includes.h"

// using namespace pros;
// using namespace pros::literals;
// using namespace okapi;

#ifdef __cplusplus
extern "C" {
#endif
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#endif


extern pros::Controller master;

extern pros::Motor drive_LF;
extern pros::Motor drive_RF;
extern pros::Motor drive_LB;
extern pros::Motor drive_RB;

extern pros::Motor intake;
extern pros::Motor cat;
extern pros::ADIAnalogIn cat_pot;

extern pros::Motor flipper;
extern pros::Motor cBar;

extern Ball_System ball_system;
extern Lift_Systems lift;
extern Chassis chassis;

extern pros::ADIGyro gyro;

extern int selected_auto;

#endif  // _PROS_MAIN_H_
