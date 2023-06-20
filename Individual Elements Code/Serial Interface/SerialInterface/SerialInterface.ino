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


  Distance to steps factor
---------------------------
  Roller Diameter       = 58mm
  Roller Circumference  = 182.2124mm
  1mm Linear travel     = 0.506°  = 0.281 steps
  1m Linear travel      = 506°    = 281 steps 

  (πd / 360) / step angle * µstep = steps per 1mm of linear travel

  d = roller diameter
  step angle = full step angle of motor
  µstep = divisor


  Cut Motor Driver Settings (Current)
-------------------------------------
S1 = ON       - FULL STEP
S2 = ON
S3 = OFF
S4 = ON       - 1.5 Amps
S5 = ON
S6 = OFF


  Cut Motor Linear Travel Calculation
-------------------------------------

                Steps per turn x microstep setting
Steps per mm = ────────────────────────────────────── x gear ratio
                            Screw pitch



*/





/*****************************************************
   LIBRARY INCLUDES
*****************************************************/

#include <Arduino.h>  // Import the Arduino library for easy microcontroller programming
#include <AccelStepper.h>


/*****************************************************
   DEFINE PINS
*****************************************************/

#define FM_ENA_PIN 22                                 //Define pin number for motor controller enable pin
#define FM_DIR_PIN 23                                 //Define pin number for motor controller direction pin
#define FM_PUL_PIN 24                                 //Define pin number for motor controller pulse/step pin

#define CM_ENA_PIN 25                                 //Define pin number for motor controller enable pin
#define CM_DIR_PIN 26                                 //Define pin number for motor controller direction pin
#define CM_PUL_PIN 27                                 //Define pin number for motor controller pulse/step pin

#define CM_HOME_SWITCH_PIN 28                         //Define pin number for homing switch (N.O)
#define CM_LIMIT_SWITCH_MAX_PIN 29                    //Define pin number for maximum R.O.M limit switch
#define CM_LIMIT_SWITCH_MIN_PIN 30                    //Define pin number for minimum R.O.M limit switch

/*****************************************************
   DEFINE PARAMETERS
*****************************************************/

#define FM_MAX_SPEED 1000                             //Define maximum motor speed value
#define FM_MAX_ACCEL 1000                             //Define maximum motor acceleration value

#define CM_MAX_SPEED 1000                             //Define maximum motor speed value
#define CM_MAX_ACCEL 1000                             //Define maximum motor acceleration value

#define FM_CIRCUMFERENCE 182.2                        //Define circumference of feed roller
#define FM_STEP_ANGLE 1.8                             //Define step angle of motor
#define FM_MICROSTEP_SETTING 8                        //Define the microstep setting of the motor controller

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

#define FM_D2S_FACTOR CIRCUMFERENCE / STEP_ANGLE * MICROSTEP_SETTING      //Defines the distance to steps factor

#define CM_STEPS_PER_TURN CM_STEP_ANGLE*360                                                               //Calculate number of steps per full turn of motor
#define CM_S2L_FACTOR ((CM_STEPS_PER_TURN * CM_MICROSTEP_SETTING) / CM_SCREW_PITCH) * CM_GEAR_RATIO       //Calculate number of steps per 1mm linear travel of carriage


/*****************************************************
   DECLARE VARIABLES & CONSTANTS
*****************************************************/

String cableID;                                       // Declare a string variable to store the cable ID
int cableLength;                                      // Declare an integer variable to store the cable length
int cableGauge;                                       // Declare an integer variable to store the cable gauge
boolean newData = false;                              // Declare and initialize a boolean flag for new data received
boolean paused = false;                               // Declare and initialize a boolean flag for the paused state

int CM_homing_pos = 0;                                //Declare global variable for homing position



/*****************************************************
   DECLARE OBJECTS
*****************************************************/

AccelStepper FeedMotor(AccelStepper::DRIVER, FM_PUL_PIN, FM_DIR_PIN);     //Create class for feed motor
AccelStepper CutMotor(AccelStepper::DRIVER, CM_PUL_PIN, CM_DIR_PIN);     //Create class for cut motor


//===============================================================================================================================================
//===============================================================================================================================================


/*──────────────────────────────────────
   CM STARTUP HOMING POSITION
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

void setup()
{
  Serial.begin(9600);                                 // Initialize serial communication at 9600 baud rate
  Serial.println("OpenCut Machine Connected");        // Print a connection message to the serial monitor

  FeedMotor.setEnablePin(FM_ENA_PIN);                 //Declare feed motor enable pin [Must be manually declared when using driver type in class]
  FeedMotor.setPinsInverted(false, false, true);      //Invert the logic of the enable pin (step, direction, enable)
  FeedMotor.setMaxSpeed(FM_MAX_SPEED);                //Set speed = steps/second
  FeedMotor.setAcceleration(FM_MAX_ACCEL);            //Set acceleration = steps/(second)^2

  FeedMotor.disableOutputs();                         //Prevent current flow to motor (prevents overheating)

  CutMotor.setEnablePin(CM_ENA_PIN);                  //Declare feed motor enable pin [Must be manually declared when using driver type in class]
  CutMotor.setPinsInverted(false, false, true);       //Invert the logic of the enable pin (step, direction, enable)
  CutMotor.setMaxSpeed(CM_MAX_SPEED);                 //Set speed = steps/second
  CutMotor.setAcceleration(CM_MAX_ACCEL);             //Set acceleration = steps/(second)^2
  CutMotor.enableOutputs();                           //Enable outputs on motor controller (allow current flow to motor)

  CM_startup_homing_sequence();                      //Call function for homing cut motor at startup

  Serial.println("Setup Complete");                   //Print to serial monitor
}

/*──────────────────────────────────────
   MAIN PROGRAM
──────────────────────────────────────*/

void loop()
{
  if (Serial.available())                             // Check if there is serial data available
  {                   
    if (!paused && Serial.peek() == '<')              // If not paused and a start delimiter ('<') is detected
    {    
      Serial.read();                                  // Consume the '<'
      cableID = Serial.readStringUntil(',');          // Read and store the cable ID until a comma is encountered
      cableLength = Serial.parseInt();                // Read and store the cable length as an integer
      cableGauge = Serial.parseInt();                 // Read and store the cable gauge as an integer

      if (Serial.read() == '>')                       // If an end delimiter ('>') is detected
      {             
        newData = true;                               // Set the newData flag to true
      }
    }
    
    else
    {
      String command = Serial.readStringUntil('\n');  // Read and store the command until a newline is encountered
      command.trim();                                 // Remove any leading or trailing whitespace

      if (command == "pause" && !paused)              // If the command is "pause" and the machine is not already paused
      {                                             
        paused = true;                                // Set the paused flag to true
        Serial.println("--  Machine paused  --");     // Print a paused message to the serial monitor
      }
      
      else if (command == "resume" && paused)         // If the command is "resume" and the machine is paused
      {                                      
        paused = false;                               // Set the paused flag to false
        Serial.println("--  Machine resumed --");     // Print a resumed message to the serial monitor
      }
      
      else if (paused)
      {                                               // If the system is paused
        Serial.println("\n!!!  System is paused, cannot execute instruction  !!!\n");  // Print an error message to the serial monitor
      }
    }
  }

  if (newData)                                        // If the newData flag is true
  {                             
    Serial.println("--------------------");           // Print a separator line to the serial monitor
    Serial.print("Cable ID: ");                       // Print "Cable ID: " to the serial monitor
    Serial.println(cableID);                          // Print the cable ID to the serial monitor
    Serial.print("Cable Length: ");                   // Print "Cable Length: " to the serial monitor
    Serial.println(cableLength);                      // Print the cable length to the serial monitor
    Serial.print("Cable Gauge: ");                    // Print "Cable Gauge: " to the serial monitor
    Serial.println(cableGauge);                       // Print the cable gauge to the serial monitor
    Serial.println("--------------------");           // Print a separator line to the serial monitor
    newData = false;                                  // Reset the newData flag to false
  }
}