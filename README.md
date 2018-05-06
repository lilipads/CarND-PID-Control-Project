# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

There's an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

## Overview
In this project, I used a PD controller for steering and a P controller for throttle to control the car. The P part is proportional to the error: for steering it is the distance from the desired track, and for throttle, it is the speed difference from the speed limit. The D part is proportional to the gradient of the error; we use to it in steering control to minimize the wobbling. I did not use the I term in a PID controller as I didn't not find systematic drifting issues.

## Parameter Tuning
The twiddle class is responsible for parameter tuning. However, in reality, it was not particularly helpful. It is highly sensitive to the initialization. In addition, given there is no way to speed up the simulator, it took excruciatingly long before convergence. 

The key to make the car drive on track ends up to be controlling the speed. I set a speed limit of 20 and use a P controller to achieve that. Lower speed reduces oscillaton from steering.

## Final Results

![Alt Text] (https://d3uik7083b30dy.cloudfront.net/items/1c0C3A11062E3s1G2Q2e/Screen%20Recording%202018-05-06%20at%2004.08%20PM.gif)
