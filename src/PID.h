#ifndef PID_H
#define PID_H

#include "twiddle.h"
#include <iostream>
#include <vector>

using namespace std;

class PID {
public:
  bool TuningMode;

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
  void Init();

  /*
   * run the twiddle algorithm and re-initialize the class
   * return true when a twiddle cycle completes and need to reset
   */ 
  bool RunTwiddle(double cte, double speed);

  /*
  * Return steering angle
  */
  double GetSteering(double cte);

 /*
  * Return throttle
  */
  double GetThrottle(double speed);

  /*
  * completed tuning
  */
  bool TwiddleCompleted();

private:
  // count number of times this controller is being called. Used in twiddle.
  int iteration;

  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;

  /*
   * Use twiddle to tune parameters
   */
  Twiddle twiddle;

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateSteeringError(double cte);

  /*
  * Reset PID with given Kp, Ki, and Kd in a vector. Used for twiddle.
  */
  void Reset(vector<double> params);
};

#endif /* PID_H */
