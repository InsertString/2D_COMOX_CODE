#ifndef _PID_H_
#define _PID_H_

class PID {
public:
  PID();
  void set_Constants(double p, double i, double d);
  void set_pid_vars(int targ, int int_limit, bool cont_int, int const_integral_val);

  double kp;
  double ki;
  double kd;

  int target;

  int output(double current, int max_out);
  int error;
  int past_error;
  int time_interval;
  int integral_limit;
  int integral;
  int derivative;
  bool const_integral;
  int const_integral_value;
};

#endif
