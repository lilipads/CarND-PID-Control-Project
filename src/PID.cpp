#include "PID.h"
#include "math.h"

const double KP_STEERING = 0.18;
const double KI = 0;
const double KD = 2.50;
const double KP_THROTTLE = 0.1;
const bool TUNING_MODE = false;
// iterations per twiddle cycle
const int MAX_ITERATION = 2000;
// after this iteration, we start counting error for twiddle
const int INITIAL_ITERATION = 100;
const int SPEED_LIMIT = 20;

PID::PID() {
	Init();
}

PID::~PID() {}

void PID::Init() {
	Kp = KP_STEERING;
	Ki = KI;
	Kd = KD;
	i_error = 0.0;
	p_error = 0.0;
	d_error = 0.0;
	TuningMode = TUNING_MODE;
	if (TuningMode){
		iteration = 0;
		twiddle.SetParams(Kp, Ki, Kd);
	}
}

void PID::Reset(vector<double> params){
	Kp = params[0];
	Ki = params[1];
	Kd = params[2];
	i_error = 0.0;
	p_error = 0.0;
	d_error = 0.0;
	iteration = 0;
	twiddle.ResetError();
}

/*
 * return true to have the main program to reset the car
 */
bool PID::RunTwiddle(double cte, double speed){
	iteration++;
	if (iteration > INITIAL_ITERATION){
		twiddle.UpdateError(cte, speed);
	}

	if (iteration == MAX_ITERATION){
		vector<double> params = twiddle.Run();
		Reset(params);
		return true;
	}
	return false;
}

void PID::UpdateSteeringError(double cte) {
	d_error = cte - p_error;
	p_error = cte;
	i_error += cte;
}

double PID::GetSteering(double cte) {
	UpdateSteeringError(cte);
	// keep it between -1 and 1
	return -std::min(std::max(Kp * p_error + Ki * i_error + Kd * d_error, -1.0), 1.0);
}

double PID::GetThrottle(double speed) {
	return (SPEED_LIMIT - speed) * KP_THROTTLE;
}

bool PID::TwiddleCompleted(){
	if (twiddle.IsCompleted()){
		std::cout << "TWIDDLE COMPLETED!" << endl;
		std::cout << "Kp: " << Kp << " Ki: " << Ki << " Kd: " << Kd << endl;
	}
	return twiddle.IsCompleted();
}