/*

Abbreviations
-------------------------
  FM = Feed Motor
  CM = Cut Motor
  ENA = Enable
  DIR = Direction
  PUL = Pulse (A.K.A Step)
  CW = Clockwise
  CCW = Counter Clockwise

╔═══════════════════════════════════════════════════════════════════════════════════════════════════╗
║                          TB6600 STEPPER MOTOR DRIVER DIP SWITCH SETTINGS                          ║
╠═════╦═════╦═════╦═══════════════╦═══════════╦══╦═════╦═════╦═════╦═════════════╦══════════════════╣
║  S1 ║  S2 ║  S3 ║ µStep Setting ║ Pulse/Rev ║  ║  S4 ║  S5 ║  S6 ║ CURRENT (A) ║ PEAK CURRENT (A) ║
╠═════╬═════╬═════╬═══════════════╬═══════════╣  ╠═════╬═════╬═════╬═════════════╬══════════════════╣
║  ON ║  ON ║  ON ║       NC      ║     NC    ║  ║  ON ║  ON ║  ON ║     0.5     ║        0.7       ║
╠═════╬═════╬═════╬═══════════════╬═══════════╣  ╠═════╬═════╬═════╬═════════════╬══════════════════╣
║  ON ║  ON ║ OFF ║   FULL STEP   ║    200    ║  ║  ON ║ OFF ║  ON ║     1.0     ║        1.2       ║
╠═════╬═════╬═════╬═══════════════╬═══════════╣  ╠═════╬═════╬═════╬═════════════╬══════════════════╣
║  ON ║ OFF ║  ON ║    1/2 STEP   ║    400    ║  ║  ON ║  ON ║ OFF ║     1.5     ║        1.7       ║
╠═════╬═════╬═════╬═══════════════╬═══════════╣  ╠═════╬═════╬═════╬═════════════╬══════════════════╣
║ OFF ║  ON ║  ON ║    1/2 STEP   ║    400    ║  ║  ON ║ OFF ║ OFF ║     2.0     ║        2.2       ║
╠═════╬═════╬═════╬═══════════════╬═══════════╣  ╠═════╬═════╬═════╬═════════════╬══════════════════╣
║  ON ║ OFF ║ OFF ║    1/4 STEP   ║    800    ║  ║ OFF ║  ON ║  ON ║     2.5     ║        2.7       ║
╠═════╬═════╬═════╬═══════════════╬═══════════╣  ╠═════╬═════╬═════╬═════════════╬══════════════════╣
║ OFF ║  ON ║ OFF ║    1/8 STEP   ║    1600   ║  ║ OFF ║ OFF ║  ON ║     2.8     ║        2.9       ║
╠═════╬═════╬═════╬═══════════════╬═══════════╣  ╠═════╬═════╬═════╬═════════════╬══════════════════╣
║ OFF ║ OFF ║  ON ║   1/16 STEP   ║    3200   ║  ║ OFF ║  ON ║ OFF ║     3.0     ║        3.2       ║
╠═════╬═════╬═════╬═══════════════╬═══════════╣  ╠═════╬═════╬═════╬═════════════╬══════════════════╣
║ OFF ║ OFF ║ OFF ║   1/32 STEP   ║    6400   ║  ║ OFF ║ OFF ║ OFF ║     3.2     ║        4.0       ║
╚═════╩═════╩═════╩═══════════════╩═══════════╩══╩═════╩═════╩═════╩═════════════╩══════════════════╝


Cut Motor Driver Settings (Current)
-----------------------------------
S1 = ON       - FULL STEP
S2 = ON
S3 = OFF
S4 = ON       - 1.5 Amps
S5 = ON
S6 = OFF

Cut Motor Linear Travel Calculation
-----------------------------------

                Steps per turn x microstep setting
Steps per mm = ────────────────────────────────────── x gear ratio
                            Screw pitch


/*****************************************************
   LIBRARY INCLUDES
*****************************************************/

#include <AccelStepper.h>

/*****************************************************
   DEFINE PINS
*****************************************************/

#define CM_ENA_PIN 8                                  //Define pin number for motor controller enable pin
#define CM_DIR_PIN 5                                  //Define pin number for motor controller direction pin
#define CM_PUL_PIN 2                                  //Define pin number for motor controller pulse/step pin
#define CM_HOME_SWITCH_PIN 10                         //Define pin number for homing switch (N.O)
#define CM_LIMIT_SWITCH_MAX_PIN 11                    //Define pin number for maximum R.O.M limit switch
#define CM_LIMIT_SWITCH_MIN_PIN 12                    //Define pin number for minimum R.O.M limit switch

/*****************************************************
   DEFINE PARAMETERS
*****************************************************/

#define CM_MAX_SPEED 1000                             //Define maximum motor speed value
#define CM_MAX_ACCEL 1000                             //Define maximum motor acceleration value


#define CM_STEP_ANGLE 1.8                              //Define step angle of motor
#define CM_MICROSTEP_SETTING 1                         //Define the microstep setting of the motor controller
#define CM_GEAR_RATIO 49                               //Define gear ratio 1:49
#define CM_SCREW_PITCH 2                               //Define lead screw pitch in mm

/*
╔═══════════════════════════════════════════════╗
║                      NOTE                     ║
║ Microstep setting value determined as follows ║
╠═══════════════════════════╦═══════════════════╣
║         Full step         ║         1         ║
╠═══════════════════════════╬═══════════════════╣
║          1/2 step         ║         2         ║
╠═══════════════════════════╬═══════════════════╣
║          1/4 step         ║         4         ║
╠═══════════════════════════╬═══════════════════╣
║          1/8 step         ║         8         ║
╠═══════════════════════════╬═══════════════════╣
║         1/16 step         ║         16        ║
╠═══════════════════════════╬═══════════════════╣
║         1/32 step         ║         32        ║
╚═══════════════════════════╩═══════════════════╝
*/

#define CM_STEPS_PER_TURN CM_STEP_ANGLE*360                                                               //Calculate number of steps per full turn of motor
#define CM_S2L_FACTOR ((CM_STEPS_PER_TURN * CM_MICROSTEP_SETTING) / CM_SCREW_PITCH) * CM_GEAR_RATIO       //Calculate number of steps per 1mm linear travel of carriage

/*****************************************************
   DECLARE VARIABLES & CONSTANTS
*****************************************************/

int CM_homing_pos = 0;                                //Declare global variable for homing position


AccelStepper CutMotor(AccelStepper::DRIVER, CM_PUL_PIN, CM_DIR_PIN);     //Create class for cut motor

/*──────────────────────────────────────
   STARTUP HOMING POSITION
──────────────────────────────────────*/

void CM_startup_homing_sequence()                     //Declare function for homing cut motor at startup
{
  CutMotor.setEnablePin(CM_ENA_PIN);                  //Declare feed motor enable pin [Must be manually declared when using driver type in class]
  CutMotor.setPinsInverted(false, false, true);       //Invert the logic of the enable pin (step, direction, enable)
  CutMotor.setMaxSpeed(CM_MAX_SPEED);                 //Set speed = steps/second
  CutMotor.setAcceleration(CM_MAX_ACCEL);             //Set acceleration = steps/(second)^2
  CutMotor.enableOutputs();                           //Enable outputs on motor controller (allow current flow to motor)

  Serial.println("Cut motor homing...");              //Print to serial monitor

  while(digitalRead(CM_HOME_SWITCH_PIN))              //Rotate CCW until homing switch is pressed
  {
    CutMotor.moveTo(CM_homing_pos);                   //Move cut motor to homing position
    CM_homing_pos--;                                  //Decrement homing position
    CutMotor.run();                                   //Run cut motor
    delay(50);                                        //Delay 50ms to prevent motor stepping too fast and causing damage
  }

  CM_homing_pos = 1;
  CutMotor.setCurrentPosition(0);                     //Set home position to zero
  

  while(!digitalRead(CM_HOME_SWITCH_PIN))             //Rotate CW until homing switch is not pressed
  {
    CutMotor.moveTo(CM_homing_pos);                   //Move cut motor to homing position
    CM_homing_pos++;                                  //Increment homing position
    CutMotor.run();                                   //Run cut motor
    delay(50);                                        //Delay 50ms to prevent motor stepping too fast and causing damage
  }  

  CutMotor.setCurrentPosition(0);                     //Set home position to zero
  CutMotor.disableOutputs();                          //Prevent current flow to motor (prevents overheating)

  Serial.print("Cut Motor Position: ");               //Print to serial monitor
  Serial.print(CM_homing_pos);                        //Print value of homing position to serial monitor (must always be zero)
}


/*──────────────────────────────────────
   SETUP
──────────────────────────────────────*/


void setup()                                          //Setup function
{
  Serial.begin(9600);                                 //Initialise serial communication at 9600 baud

  while (!Serial);                                    //Wait for serial communication to be established
  {
    //Do nothing
  }
  
  delay(500);                                         //Wait 500ms
  Serial.println("Serial communication initialised");             //Print to serial monitor

  pinMode(CM_HOME_SWITCH_PIN, INPUT_PULLUP);          //Set home switch pin as input (active low)
  pinMode(CM_LIMIT_SWITCH_MAX_PIN, INPUT_PULLUP);     //Set maximum limit switch pin as input (active low)
  pinMode(CM_LIMIT_SWITCH_MIN_PIN, INPUT_PULLUP);     //Set minimum limit switch pin as input (active low)

  CM_startup_homing_sequence();                      //Call function for homing cut motor at startup
  
  Serial.println("\nSetup Complete");                 //Print to serial monitor
}


/*──────────────────────────────────────
   MAIN PROGRAM
──────────────────────────────────────*/

void loop()                                           //Main Program
{
  while (!Serial.available())                         //Wait for serial data to become available in serial buffer
  {
    // do nothing
  }

  int distance = Serial.parseInt();                   //Read the linear distance value from the serial monitor

  
  int steps = map(distance, 0, 100, 0, CM_S2L_FACTOR);    //Map the linear distance to a number of steps

  
  Serial.print("Distance (linear): ");                 //Print to serial monitor
  Serial.print(distance);                              //Print linear distance to serial monitor
  Serial.print("mm, Steps: ");                         //Print to serial monitor
  Serial.println(steps);                               //Print number of steps to serial monitor


  CutMotor.enableOutputs();                           //Enable outputs on motor controller (allow current flow to motor)
  CutMotor.setCurrentPosition(0);                     //Set current motor position as zero (this does not move the motor to position zero it sets the stored position to zero)
  CutMotor.moveTo(steps);                             //Move the feed motor by the number of steps required

  while (CutMotor.isRunning())                        //While the motor is in motion
  {
    CutMotor.run();                                   //Advance motor to next step
  }

  CutMotor.disableOutputs();                          //Disable the outputs on the motor controller (prevent current flowing to motor)
  delay(1000);                                        //Wait 1 sec
  CutMotor.setCurrentPosition(0);                     //Set motor position as zero
}

