#include "main.h"

void autonomous() {
  resetTimer(AUTO_TIMER);
  chassis.reset_chassis_auto_vars();
  while (getTime(AUTO_TIMER) < 15000) {

    switch (selected_auto) {
      case 0 :
      flag_auto(RED);
      break;
      case 1 :
      flag_auto(BLUE);
      break;
    }
  }
}
