#ifndef _ROBOT_CLASSES_H_
#define _ROBOT_CLASSES_H_

class Chassis {
public:
  void setLeftPower(int power);
  void setRightPower(int power);

  void drive();
};


class Ball_System {
public:
  void setIntakePower(int power);

  void setFlywheelPower(int power);
  void setFlywheelRPM(int target);

  void drive();
};

#endif
