#include "main.h"
#include "robot_includes/robot_classes.h"




Ball_System::Ball_System() {
  target = IDLE;
}




void Ball_System::setIntakePower(int power) {
  intake = -power;
}




Cat_Positions Ball_System::current_cat_position() {
  Cat_Positions return_state = IDLE;
  if (cat_pot.get_value() < 1450 && cat_pot.get_value() > 1550) {
    return_state = LOAD;
  }
  else if (cat_pot.get_value() < 1550) {
    return_state = FIRE;
  }
  else if (cat_pot.get_value() > 1450) {
    return_state = IDLE;
  }
  return return_state;
}



void Ball_System::setCatpower(int power) {
  cat = -power;
}




void Ball_System::setCatPosition() {

  switch (target) {
    case LOAD :
    if (current_cat_position() == IDLE) {
      setCatpower(127);
    }
    else if (current_cat_position() == LOAD) {
      setCatpower(-10);
    }
    break;
    case FIRE :
    if (current_cat_position() == IDLE) {
      setCatpower(0);
    }
    else if (current_cat_position() == LOAD) {
      setCatpower(127);
    }
    break;
    case IDLE :
    if (current_cat_position() == IDLE) {
      setCatpower(0);
    }
    else if (current_cat_position() == LOAD) {
      setCatpower(-127);
    }
    break;
  }
}





void Ball_System::drive() {
  setCatPosition();

  if (master.get_digital_new_press(DIGITAL_R1) && target != LOAD) {
    target = LOAD;
  }
  else if (master.get_digital_new_press(DIGITAL_R1) && target == LOAD && current_cat_position() == LOAD) {
    target = FIRE;
  }
  else if (master.get_digital_new_press(DIGITAL_R2) && target != IDLE) {
    target = IDLE;
  }


  if (current_cat_position() == LOAD) {
    if (master.get_digital(DIGITAL_L1)) {
      setIntakePower(127);
    }
    else if (master.get_digital(DIGITAL_L2)) {
      setIntakePower(-127);
    }
    else {
      setIntakePower(0);
    }
  }
  else if (current_cat_position() != LOAD) {
    if (master.get_digital(DIGITAL_L2)) {
      setIntakePower(-127);
    }
    else {
      setIntakePower(0);
    }
  }
}
