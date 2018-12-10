#include "main.h"
#include "robot_includes/pid.h"

PID::PID() {
  kp = 0;
  ki = 0;
  kd = 0;

  target = 0;
  error = 0;
  past_error = 0;
  integral_limit = 0;
  integral = 0;
  derivative = 0;
  time_interval = 20;
  const_integral = false;
}





void PID::set_Constants(double p, double i, double d) {
  kp = p;
  ki = i;
  kd = d;
}





void PID::set_pid_vars(int targ, int int_limit, bool const_int, int const_integral_val) {
  target = targ;
  if (const_int == true) {
    const_integral_value = const_integral_val;
  }
  integral_limit = int_limit;
}




int PID::output(double current, int max_out) {
  int out;

  past_error = error;

  error = target - current;

  if (const_integral == false) {
    if (abs(error) < integral_limit)
      integral += error;
    else
      integral = 0;
  }
  else {
    if (error > 0)
      integral = const_integral_value;
    else if (error < 0)
      integral = -const_integral_value;
  }

  derivative = (error - past_error) / time_interval;

  out = (error * kp) + (integral * ki) + (derivative * kd);

  if (out > max_out) out = max_out;
  else if (out < (-max_out)) out = -max_out;
  else out = out;

  return out;
}
