/*
 * to fine tune the PID parameters
 */

#include "twiddle.h"

const double TOLERANCE = 0.001;

Twiddle::Twiddle() {
  Init();
}

Twiddle::~Twiddle() {}

void Twiddle::Init(){
  params = {0.0, 0.0, 0.0};
  deltas = {0.1, 0.1, 0.1};
  best_error = std::numeric_limits<double>::infinity();
  error = 0;
  tuning_param_index = 0;
  stage = 0;
}

void Twiddle::SetParams(double Kp, double Ki, double Kd){
  params = {Kp, Ki, Kd};
}

vector<double> Twiddle::Run(){
  cout << "error: " << error << endl;
  bool tune_next_param = false;

  switch (stage){
    case 0: {
      if (error < best_error){
        best_error = error;
        cout << "BEST ERROR" << endl;
        deltas[tuning_param_index] *= 1.1;
        tune_next_param = true;
      } else{
        params[tuning_param_index] -= 2 * deltas[tuning_param_index];
        stage++;
      }
    } break;
    case 1: {
      if (error < best_error){
        best_error = error;
        cout << "BEST ERROR" << endl;
        deltas[tuning_param_index] *= 1.1;
      } else {
        params[tuning_param_index] += deltas[tuning_param_index];
        deltas[tuning_param_index] *= 0.9;
      }
      tune_next_param = true;
    }
  }

  if (tune_next_param){
    stage = 0;
    tuning_param_index  = 2 - tuning_param_index;
    params[tuning_param_index] += deltas[tuning_param_index];
    tune_next_param = false;
  }

  cout << "new stage: " << stage << " new tuning index: " << tuning_param_index << " new params: " << params[0] <<
  " " << params[1] << " " << params[2] << 
  " new delta: " << deltas[0] << " " << deltas[1] << " "
  << deltas[2] << endl;
  return params;
}

bool Twiddle::IsCompleted(){
  return (deltas[0] + deltas[1] + deltas[2] < TOLERANCE);
}

void Twiddle::UpdateError(double cte, double speed){
  error += cte * cte * speed;
}

void Twiddle::ResetError(){
  error = 0;
}