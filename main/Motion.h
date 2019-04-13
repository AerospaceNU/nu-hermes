#ifndef MOTION_H
#define MOTION_H

#define rightA  4
#define rightB  5
#define leftA   6
#define leftB   22

#define rightPot  A10
#define leftPot   A11

#define LEFT  1
#define RIGHT 2

#define MAX_PWM 255

#include <arduino.h>

void turnToPoint(int side, int pwmSpeed, int angle);
void turnToPointB(int pin, int pwmSpeed, int count);
void turnToPointA(int pin, int pwmSpeed, int count);
void rotateMotor(int pin, int pwmSpeed, int len);



#endif
