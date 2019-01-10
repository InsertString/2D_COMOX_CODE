#ifndef _ROBOT_CLASSES_H_
#define _ROBOT_CLASSES_H_


#define CAT_LOADING_MAX_VAL 1550
#define CAT_LOADING_MIN_VAL 1500


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
  void setLeftPower(int power);
  void setRightPower(int power);

  void drive();
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
};

#endif
