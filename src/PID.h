#include <uWS/uWS.h>

#ifndef PID_H
#define PID_H


class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Variables for Twiddle
  */
  double dp[3];
  int flag_1;
  int p_i_d;

  double total_error;

  double best_err;

  int counter_iterations;


  /*
  * Coefficients of PID
  */
  double p[3];


  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp_in, double Ki_in, double Kd_in);

  /*
  * Update the PID error variables given cross track error.
  */
  double UpdateError(double cte, uWS::WebSocket<uWS::SERVER> ws);

  /*
  * Calculate the total PID error.
  */
  void TotalError(double cte);

  //Restart the simulator
  void Restart(uWS::WebSocket<uWS::SERVER> ws);

  //Implement Twiddle
  double twiddle();

};

#endif /* PID_H */
