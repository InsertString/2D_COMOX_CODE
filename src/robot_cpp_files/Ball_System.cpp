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
  if (cat_pot.get_value() < CAT_LOADING_MAX_VAL && cat_pot.get_value() > CAT_LOADING_MIN_VAL) {
    return_state = LOAD;
  }
  else if (cat_pot.get_value() > CAT_LOADING_MAX_VAL) {
    return_state = FIRE;
  }
  else if (cat_pot.get_value() < CAT_LOADING_MIN_VAL) {
    return_state = IDLE;
  }
  else {
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
    switch (current_cat_position()) {
      case LOAD :
      setCatpower(7);
      break;
      case IDLE :
      setCatpower(127);
      break;
      case FIRE :
      setCatpower(0);
      break;
    }
    break;
    case FIRE :
    switch (current_cat_position()) {
      case LOAD :
      setCatpower(127);
      break;
      case IDLE :
      setCatpower(0);
      break;
      case FIRE :
      setCatpower(127);
      break;
    }
    break;
    case IDLE :
    setCatpower(0);
    break;
  }
}





void Ball_System::drive() {
  setCatPosition();

  if (master.get_digital(DIGITAL_R2)) {
    target = IDLE;
  }
  else if (master.get_digital(DIGITAL_R1)) {
    target = LOAD;
  }
  else if (!master.get_digital(DIGITAL_R1) && target == LOAD) {
    target = FIRE;
  }




  if (master.get_digital(DIGITAL_L1) && master.get_digital(DIGITAL_R1)) {
    setIntakePower(127);
  }
  else if (master.get_digital(DIGITAL_L2)) {
    setIntakePower(-127);
  }
  else {
    setIntakePower(0);
  }

}
