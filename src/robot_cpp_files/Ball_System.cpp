#include "main.h"
#include "robot_includes/robot_classes.h"




Ball_System::Ball_System() {
  target = IDLE;
  Cat_target = 1590;
  shoot_step = 0;
  pull_back_step = 0;
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
      setCatpower(0);
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





Auto_Function Ball_System::shoot() {
  Auto_Function return_state = INCOMPLETE;

  switch (shoot_step) {
    case 0 :
    if (cat_pot.get_value() > 1200) {
      setCatpower(127);
    }
    else {
      setCatpower(0);
      shoot_step++;
    }
    break;
    case 1 :
    if (cat_pot.get_value() < 1500) {
      setCatpower(127);
    }
    else {
      setCatpower(0);
      shoot_step++;
    }
    break;
    case 2 :
    return_state = COMPLETE;
    break;
  }

  return return_state;
}




int a = 2;
int b = 0;
void Ball_System::drive() {
  //setCatPosition();
  int power = (Cat_target - cat_pot.get_value()) * 1;

  if (master.get_digital(DIGITAL_R2)) {
    setCatpower(0);
    a = 1;
    b = 1;
  }
  else if (!master.get_digital(DIGITAL_R1)) {
    a = 2;
    if (cat_pot.get_value() < 1485 && b == 1) {
      setCatpower(power);
    }
    else {
      setCatpower(0);
      b = 0;
    }
  }
  else if (master.get_digital(DIGITAL_R1) && cat_pot.get_value() > 1000 && a == 2) {
    setCatpower(127);
    b = 1;
  }
  else {
    setCatpower(0);
  }


  if (master.get_digital(DIGITAL_L1) && cat_pot.get_value() > 1200) {
    setIntakePower(127);
  }
  else if (master.get_digital(DIGITAL_L2)) {
    setIntakePower(-127);
  }
  else {
    setIntakePower(0);
  }

}
