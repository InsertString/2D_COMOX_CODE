#include "main.h"
#include "robot_includes/robot_includes.h"

#define CHAINBAR 1
#define FLIPPER 2
#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4
#define NONE 0

#define SCORING -1850
#define LIFTING -4150
#define GRABBING -280

Lift_Systems::Lift_Systems() {
  curr_system = FLIPPER;
  flipper_state = UP;
}


void Lift_Systems::setFlipperPower(int power) {
  flipper = power;
}


void Lift_Systems::setCBarPower(int power) {
  cBar = power;
}



int Lift_Systems::button_pressed() {
  int rv = NONE;
  if (master.get_digital(DIGITAL_UP)) {
    rv = UP;
  }
  else if (master.get_digital(DIGITAL_LEFT)) {
    rv = LEFT;
  }
  else if (master.get_digital(DIGITAL_DOWN)) {
    rv = DOWN;
  }
  else if (master.get_digital(DIGITAL_RIGHT)) {
    rv = RIGHT;
  }
  return rv;
}



void Lift_Systems::drive() {

  if (master.get_digital_new_press(DIGITAL_A)) {
    curr_system = FLIPPER;
  }
  else if (master.get_digital_new_press(DIGITAL_B)) {
    curr_system = CHAINBAR;
  }

  switch (button_pressed()) {
    case UP :
    if (curr_system == CHAINBAR) {
      setCBarPower(127);
    }
    else if (curr_system == FLIPPER) {
      setFlipperPower(127);
      flipper_state = UP;
    }
    break;
    case LEFT :
    if (curr_system == CHAINBAR) {
      cBar.move_absolute(LIFTING, 70);
    }
    else if (curr_system == FLIPPER) {
      flipper.move_absolute(GRABBING, 200);
    }
    break;
    case DOWN :
    if (curr_system == CHAINBAR) {
      setCBarPower(-127);
    }
    else if (curr_system == FLIPPER) {
      setFlipperPower(-127);
      flipper_state = DOWN;
    }
    break;
    case RIGHT :
    if (curr_system == CHAINBAR) {
      cBar.move_absolute(SCORING, 200);
    }
    else if (curr_system == FLIPPER) {
      setFlipperPower(0);
    }
    break;
    case NONE :
    if (curr_system == CHAINBAR) {
      setCBarPower(0);
    }
    else if (curr_system == FLIPPER) {
      if (flipper_state == UP) {
        setFlipperPower(6);
      }
      else if (flipper_state == DOWN) {
        setFlipperPower(-3);
      }
    }
    break;
  }

}
