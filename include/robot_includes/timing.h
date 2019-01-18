#ifndef _TIMING_H_
#define _TIMING_H_

#define AUTO_TIMER 0
#define DRIVE_PID_TIMEOUT 1
#define DRIVE_PID_EXIT 2
#define TURN_PID_TIMEOUT 3
#define TURN_PID_EXIT 4
#define AUTO_STEP_TIMEOUT 5

void resetTimer(int timer_slot);

int getTime(int timer_slot);

#endif
