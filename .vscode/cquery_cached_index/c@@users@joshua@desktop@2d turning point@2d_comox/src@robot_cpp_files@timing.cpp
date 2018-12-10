#include "main.h"
//#include "robot_includes/timing.h"


//20 timers
int start_time[20] = {
  0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0
};

//restets the start time in the spesific timer slot
void resetTimer(int timer_slot) {
  start_time[timer_slot] = pros::millis();
}


int getTime(int timer_slot) {
  int i;
  i = pros::millis() - start_time[timer_slot];
  return i;
}
