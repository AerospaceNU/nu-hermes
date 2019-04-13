#include "Motion.h"

// potentiometer conversion factor in deg/LSB
double POT_CONVERSION = 0.298;

int rightFlipperBias = 0;
int leftFlipperBias = 0;

void rotateMotor(int pin, int pwmSpeed, int len){

  analogWrite(pin, pwmSpeed);
  delay(len);
  analogWrite(pin, 0);
  
}

// only works for right side
void turnToPointA(int pin, int pwmSpeed, int count){

  if(pin == rightA){
  
    analogWrite(pin, pwmSpeed);

    int potPos = analogRead(rightPot);
    
    while(potPos < count){
        potPos = analogRead(rightPot);
        //Serial.println(potPos);
    }
  
    analogWrite(pin, 0);

  }else{

    analogWrite(pin, pwmSpeed);

    int potPos = analogRead(leftPot);
    //Serial.println(count);
    while(potPos < count){
        potPos = analogRead(leftPot);
        //Serial.println(potPos);
    }
  
    analogWrite(pin, 0);

    
  }
  
}

// only works for right side
void turnToPointB(int pin, int pwmSpeed, int count){

  if(pin == rightB){
  
    analogWrite(pin, pwmSpeed);
    int potPos = analogRead(rightPot);
    
    while(potPos > count){
        potPos = analogRead(rightPot);
        //Serial.println(potPos);
    }
  
    analogWrite(pin, 0);

  }else{
        
    analogWrite(pin, pwmSpeed);
    int potPos = analogRead(leftPot);
    
    while(potPos > count){
        potPos = analogRead(leftPot);
        //Serial.println(potPos);
    }
  
    analogWrite(pin, 0);

  }
  
}

void turnToPoint(int side, int pwmSpeed, int angle){

  int potPosition = 0;
  double count = angle/POT_CONVERSION;
  Serial.print("Move the flipper to: ");

  switch(side){
    
    case LEFT:
      
      Serial.println(((int) count + leftFlipperBias));
    
      // read position of gear
      potPosition = analogRead(leftPot);

      Serial.print("The flipper is at: ");
      Serial.println(potPosition);
  
      // check which direction to move the motor
      if(potPosition > (int)count){
        turnToPointB(leftB, pwmSpeed, ((int) count + leftFlipperBias));
      }else{
        turnToPointA(leftA, pwmSpeed, ((int) count + leftFlipperBias));
      }
      
      break;
      
    case RIGHT:
    
      Serial.println(((int) count + rightFlipperBias));
      
      // read position of gear
      potPosition = analogRead(rightPot);

      Serial.print("The flipper is at: ");
      Serial.println(potPosition);
      
      // check which direction to move the motor
      if(potPosition > (int)count){
        turnToPointB(rightB, pwmSpeed, ((int) count + rightFlipperBias));
      }else{
        turnToPointA(rightA, pwmSpeed, ((int) count + rightFlipperBias));
      }
      
      break;
      
    default:
      break;
  }
  
}
