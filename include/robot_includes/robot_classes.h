#include "robot_includes/pid.h"


#ifndef _ROBOT_CLASSES_H_
#define _ROBOT_CLASSES_H_


#define CAT_LOADING_MAX_VAL 1500
#define CAT_LOADING_MIN_VAL 1490


enum Auto_Function_Var {
  COMPLETE,
  INCOMPLETE,
  FLAGGED
};

enum Cat_Positions {
  LOAD,
  IDLE,
  FIRE
};


class Chassis {
public:
  Chassis();
  void setLeftPower(int power);
  void setRightPower(int power);

  void drive();
private:
  int direction;
};


class Lift_Systems {
public:
  Lift_Systems();
  void setFlipperPower(int power);
  void setCBarPower(int power);
  PID CBar_pid;
  int button_pressed();

  void drive();

  int curr_system;
private:
  int flipper_state;
};


class Ball_System {
public:
  Ball_System();
  void setIntakePower(int power);

  void setCatpower(int power);
  void setCatPosition();
  Cat_Positions current_cat_position();

  void drive();
private:
  Cat_Positions target;
  int Cat_target;
};

#endif
