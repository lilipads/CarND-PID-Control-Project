#ifndef TWIDDLE_H
#define TWIDDLE_H

#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Twiddle {
public:
  /*
  * Constructor
  */
  Twiddle();

  /*
  * Destructor.
  */
  virtual ~Twiddle();

  void Init();

	void SetParams(double Kp, double Ki, double Kd);

	/*
	 * run the core of the twiddle algorithm that adjusts
	 * parameters based on the error
	 * return new params {Kp, Ki, Kd}
   */
	vector<double> Run();

	/*
   * completed tuning
   */
	bool IsCompleted();

	/*
	 * calculate cumulative error
	 */ 
	void UpdateError(double cte, double speed);

	/*
	 * Reset error to 0
	 */
	void ResetError();

private:
	// which of the 3 params to tune. 0: Kp, 1: Ki, 2: Kd
	int tuning_param_index;

	// sum of squared cte betwee max and max * 2 iterations 
	double error;

	// lowest error by far
	double best_error;

	// vector of {Kp, Ki, Kd}
	vector<double> params;

	// vector of {dp, di, dd}
	vector<double> deltas;

	/* 
	 * stage 0: increase delta if error is lower or lower param by two deltas
	 * stage 1: increase delta if error from stage 1 is lower else decrease delta
	 */
	int stage;

};

#endif /* TWIDDLE_H */