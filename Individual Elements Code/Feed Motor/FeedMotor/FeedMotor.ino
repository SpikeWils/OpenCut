/*

FM = Feed Motor
CM = Cut Motor

*/



#include <AccelStepper.h>

/*****************************************************
   DEFINE PINS
*****************************************************/

#define FM_ENA_PIN 8
#define FM_DIR_PIN 5
#define FM_PUL_PIN 2

/*****************************************************
   DEFINE PARAMETERS
*****************************************************/

#define FM_MAX_SPEED 1000
#define FM_MAX_ACCEL 1000

/*****************************************************
   DECLARE VARIABLES & CONSTANTS
*****************************************************/

const int 

AccelStepper FeedMotor(FM_ENA_PIN, FM_DIR_PIN, FM_PUL_PIN);

void setup()
{
  Serial.begin(9600);

  while (!Serial);                                    //Wait for serial communication to be established
  {
    //Do nothing
  }
  
  delay(500);                                         //Wait 500ms
  Serial.println("Serial comm init");                 //Print to serial monitor

  FeedMotor.setMaxSpeed(FM_MAX_SPEED);                //Speed = steps/second
  FeedMotor.setAcceleration(FM_MAX_ACCEL);            //Accel = steps/(second)^2

  FeedMotor.disableOutputs();                         //Prevent current flow to motor (prevents overheating)

  Serial.println("Setup Complete")
}