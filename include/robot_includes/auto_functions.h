#include "robot_classes.h"

#ifndef _AUTO_FUNCTIONS_H_
#define _AUTO_FUNCTIONS_H_

#define RED 1
#define BLUE 2

void start_auto();
void reset_auto_variables();

void advance_auto_step(int time_out);


void flag_auto(int colour);
void park_auto(int colour);
void skills_auto(int colour);

#endif
