#include "main.h"

void autonomous() {

  resetTimer(AUTO_TIMER);
  chassis.reset_chassis_auto_vars();
  reset_auto_variables();
  while (getTime(AUTO_TIMER) < 15000) {
    //chassis.PID_turn(900, 100);
    ///*
    switch (selected_auto) {
      case 0 :
      flag_auto(RED);
      break;
      case 1 :
      flag_auto(BLUE);
      break;
    }
    //*/
  }
}
