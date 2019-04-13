#include <Arduino.h>
#include <Wire.h>
#include "Sensors.h"
#include "Motion.h"
#include "Data.h"

#define DEBUG

#define NICROME 20
#define NICROME_DELAY 15000

#define TEST_PIN_TWO 21
#define TEST_PIN_ONE 12

#define ANALOG_TEST_ONE A10
#define ANALOG_TEST_TWO A11

#define LEFT  1
#define RIGHT 2

Sensors board(19, 18);

int state = 0;
int launchTime = 0;
float previousAltitude = 0;
float launchAltitude = 0;


// Setperate Rover using nicrome
void breakNicrome()
{
  digitalWrite(NICROME, HIGH);
  Serial.println("Nicrome set to release");
  delay(NICROME_DELAY / 2);
  Serial.println("Nicrome in progress");
  delay(NICROME_DELAY / 2);
  Serial.println("Nicrome Completed");  
  digitalWrite(NICROME, LOW);
  delay(5000);
  state = 3;
}

void roverMotion()
{
  
}

void detectLaunch()
{
  float currentAltitude = board.Altitude();

  if ((currentAltitude > (previousAltitude + 30)) || currentAltitude > 300)
  {
    launchTime = millis();
    state = 1;
  }

  previousAltitude = currentAltitude;
  return;
}


void detectGround()
{
  int loopCount = 0;
  while (loopCount < 120)
  {
    loopCount++;
    delay(1000);
    Serial3.println("Ground detection");
  }

  float currentAltitude = board.Altitude();

  if (currentAltitude < 80)
  {
    delay(8000);
    state = 2;
  }
  return;
}

// this is the setup
void setup() 
{

  Serial3.begin(9600);
  Serial3.println("Rover Power up");

  #ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Begining");
  #endif

  pinModeInitAll();
  analogReference(EXTERNAL); // Sets the refrence for the ADC to the external source on pin AREF (on the inside of pin 23)

  #ifdef DEBUG
  Serial.println("Running");
  state = 4;
  #endif
  
  delay(100);
  board.init();

  digitalWrite(TEST_PIN_TWO, LOW);
  Serial3.println("Rover Initalized");
}

void pinModeInitAll()
{
  pinMode(13, OUTPUT);
  pinMode(NICROME, OUTPUT);
  digitalWrite(NICROME, LOW);
  pinMode(TEST_PIN_TWO, OUTPUT);
  pinMode(TEST_PIN_ONE, INPUT);
}

void loop() 
{
  switch (state)
  {
    case 0:
      detectLaunch();
      break;
    
    case 1:
      detectGround();
      break;

    case 2:
      breakNicrome();
      break;

    case 3:
      roverMotion();
      break;

    case 4:
      Serial3.println("in startup mode");

      if (digitalRead(TEST_PIN_ONE));
      {
        Serial3.println("Entering manual override mode");
      }
      break;
     
    default:
      break;
      Serial.print("Current Rover state: ");
      Serial.println(state);
  }

  #ifdef DEBUG
  Serial.println(digitalRead(TEST_PIN_ONE));
  #endif

  if (digitalRead(TEST_PIN_ONE))
  {
    #ifdef DEBUG
    Serial.println("Running Flip");
    #endif

    turnToPoint(LEFT, 175, 180);
    turnToPoint(LEFT, 200, 0);
    delay(500);
    turnToPoint(RIGHT, 175, 180);
    turnToPoint(RIGHT, 200, 0);
    
  }

  #ifdef DEBUG
  Serial.println(board.Altitude());
  Serial.println(board.XAccel());
  Serial.println(board.YAccel());
  Serial.println(board.ZAccel());
  Serial.println("TEST");
  #endif

  state = processSignal(state);
  delay(500);

}




// Data
// Used to communicate with the outside world, through radio,
// or other serial connections
