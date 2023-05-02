/*

Abbreviations
-------------------------
FM = Feed Motor
CM = Cut Motor
ENA = Enable
DIR = Direction
PUL = Pulse (A.K.A Step)


Distance to steps factor
-------------------------
  Roller Diameter       = 58mm
  Roller Circumference  = 182.2124mm
  1mm Linear travel     = 0.506°  = 0.281 steps
  1m Linear travel      = 506°    = 281 steps 

  (πd / 360) / step angle * microstep = steps per 1mm of linear travel

  d = roller diameter
  step angle = full step angle of motor
  microstep = divisor (e.g full step = 1, half step = 1/2, etc.)

*/



#include <AccelStepper.h>

/*****************************************************
   DEFINE PINS
*****************************************************/

#define FM_ENA_PIN 8                                  //Define pin number for motor controller enable pin
#define FM_DIR_PIN 5                                  //Define pin number for motor controller direction pin
#define FM_PUL_PIN 2                                  //Define pin number for motor controller pulse/step pin

/*****************************************************
   DEFINE PARAMETERS
*****************************************************/

#define FM_MAX_SPEED 1000                             //Define maximum motor speed value
#define FM_MAX_ACCEL 1000                             //Define maximum motor acceleration value

#define CIRCUMFERENCE 182.2                           //Define circumference of feed roller
#define STEP_ANGLE 1.8                                //Define step angle of motor
#define MICROSTEP_SETTING 8                           //Define the microstep setting of the motor controller

/*------------------------------------------------
| NOTE:                                           |
|                                                 |
| Micro step setting value determined as follows  |
| Full step = 1                                   |
| 1/2 step  = 2                                   |
| 1/4 step  = 4                                   |
| 1/8 step  = 8                                   |
| 1/16 step = 16                                  |
| 1/32 step = 32                                  |
-------------------------------------------------*/

#define FM_D2S_FACTOR CIRCUMFERENCE / STEP_ANGLE * MICROSTEP_SETTING      //Defines the distance to steps factor

/*****************************************************
   DECLARE VARIABLES & CONSTANTS
*****************************************************/



AccelStepper FeedMotor(AccelStepper::DRIVER, FM_PUL_PIN, FM_DIR_PIN);     //Create class for feed motor


void setup()                                          //Setup function
{
  Serial.begin(9600);                                 //Initialise serial communication at 9600 baud

  while (!Serial);                                    //Wait for serial communication to be established
  {
    //Do nothing
  }
  
  delay(500);                                         //Wait 500ms
  Serial.println("Serial comm init");                 //Print to serial monitor

  FeedMotor.setEnablePin(FM_ENA_PIN);                 //Declare feed motor enable pin [Must be manually declared when using driver type in class]
  FeedMotor.setPinsInverted(false, false, true);      //Invert the logic of the enable pin (step, direction, enable)
  FeedMotor.setMaxSpeed(FM_MAX_SPEED);                //Set speed = steps/second
  FeedMotor.setAcceleration(FM_MAX_ACCEL);            //Set acceleration = steps/(second)^2

  FeedMotor.disableOutputs();                         //Prevent current flow to motor (prevents overheating)

  Serial.println("Setup Complete");                   //Print to serial monitor
}




void loop()                                           //Main Program
{
  while (!Serial.available())                         //Wait for serial data to become available in serial buffer
  {
    // do nothing
  }

  int distance = Serial.parseInt();                   //Read the linear distance value from the serial monitor

  
  int steps = map(distance, 0, 100, 0, FM_D2S_FACTOR);    //Map the linear distance to a number of steps

  
  Serial.print("Distance (linear): ");                 //Print to serial monitor
  Serial.print(distance);                              //Print linear distance to serial monitor
  Serial.print("mm, Steps: ");                         //Print to serial monitor
  Serial.println(steps);                               //Print number of steps to serial monitor
  Serial.println(FM_D2S_FACTOR);                       //Print Feed motor D2S factor to serial monitor 

  FeedMotor.enableOutputs();                           //Enable outputs on motor controller (allow current flow to motor)
  FeedMotor.setCurrentPosition(0);                     //Set current motor position as zero (this does not move the motor to position zero it sets the stored position to zero)
  FeedMotor.moveTo(steps);                             //Move the feed motor by the number of steps required

  while (FeedMotor.isRunning())                        //While the motor is in motion
  {
    FeedMotor.run();                                   //Advance motor to next step
  }

  FeedMotor.disableOutputs();                          //Disable the outputs on the motor controller (prevent current flowing to motor)
  delay(1000);                                         //Wait 1 sec
  FeedMotor.setCurrentPosition(0);                     //Set motor position as zero
}

