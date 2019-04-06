#ifndef MOTION_H
#define MOTION_H

#include <BasicStepperDriver.h>
#include <DRV8834.h>

#define MOTOR_STEPS 200
#define RPM 320

#define MICROSTEPS 1

#define DIR_LEFT 4
#define STEP_LEFT 5

#define DIR_RIGHT 6
#define STEP_RIGHT 22

#define LEFT_SIDE 1
#define RIGHT_SIDE 2


void initSteppers();
void flipRover(int side);

#endif
