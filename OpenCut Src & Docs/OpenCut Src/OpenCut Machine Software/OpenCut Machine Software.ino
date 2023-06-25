/*
    ▄██████▄     ▄███████▄    ▄████████ ███▄▄▄▄    ▄████████ ███    █▄      ███
   ███    ███   ███    ███   ███    ███ ███▀▀▀██▄ ███    ███ ███    ███ ▀█████████▄
   ███    ███   ███    ███   ███    █▀  ███   ███ ███    █▀  ███    ███    ▀███▀▀██
   ███    ███   ███    ███  ▄███▄▄▄     ███   ███ ███        ███    ███     ███   ▀
   ███    ███ ▀█████████▀  ▀▀███▀▀▀     ███   ███ ███        ███    ███     ███
   ███    ███   ███          ███    █▄  ███   ███ ███    █▄  ███    ███     ███
   ███    ███   ███          ███    ███ ███   ███ ███    ███ ███    ███     ███
    ▀██████▀   ▄████▀        ██████████  ▀█   █▀  ████████▀  ████████▀     ▄████▀


|----------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Abbreviations and Acronyms:                                                                                                                                    |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------|
|                                                                                                                                                                |
| ADC   = Analog to Digital Converter: A device that converts analog signals into digital numbers.                                                               |
| ANDON = Andon System: A manufacturing term referring to a system notifying management, maintenance, and other workers of a quality or process problem.         |
| CCW   = Counterclockwise: Referring to a counterclockwise rotation or movement.                                                                                |
| CM    = Cut Motor: Referring to the cutting motor in the machine.                                                                                              |
| CW    = Clockwise: Referring to a clockwise rotation or movement.                                                                                              |
| D2S   = Distance to Steps: The conversion factor from distance to steps for a motor.                                                                           |
| DIR   = Direction: Used for the direction signal pin on the motor drivers, controlling motor rotation direction.                                               |
| ENA   = Enable: Used for the enable signal pin on the motor drivers, activating or deactivating the motor.                                                     |
| FM    = Feed Motor: Referring to the feeding motor in the machine.                                                                                             |
| GRN   = Green: Referring to the color of an LED or signal lamp.                                                                                                |
| ID    = Identifier: A unique identification for cables.                                                                                                        |
| intlk = Interlock: A mechanism ensuring that certain conditions are met before actions are executed.                                                           |
| ISR   = Interrupt Service Routine: A function that handles the actions required at the time of an interrupt.                                                   |
| PDU   = Power Distribution Unit: Subsystem providing control and distribution of electric power.                                                               |
| PUL   = Pulse: Used for the pulse signal pin on the motor drivers, controlling motor steps.                                                                    |
| RED   = Red: Referring to the color of an LED or signal lamp.                                                                                                  |
| YEL   = Yellow: Referring to the color of an LED or signal lamp.                                                                                               |
|                                                                                                                                                                |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------|



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


  Feed Motor Driver Settings (Current)
  -------------------------------------
  S1 = ON       - FULL STEP
  S2 = ON
  S3 = OFF
  S4 = ON       - 1.5 Amps
  S5 = ON
  S6 = OFF

  Distance to steps factor
  -------------------------
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
  S1 = OFF      - 1/8 STEP
  S2 = ON
  S3 = OFF
  S4 = OFF       - 2.5 Amps
  S5 = ON
  S6 = ON


  Cut Motor Linear Travel Calculation
  -------------------------------------

                    Steps per turn x microstep setting
  Steps per mm = ────────────────────────────────────── x gear ratio
                              Screw pitch
                                                                                                                                               
 */

/**********************************************************************************************************
   INCLUDES
**********************************************************************************************************/

#include <Arduino.h>                                  //Import the Arduino library (necessary for non Arduino MCUs)
#include <AccelStepper.h>                             //https://github.com/waspinator/AccelStepper
#include "CableIDPrinter.h"                           //

/**********************************************************************************************************
   DEFINE PINS
**********************************************************************************************************/

#define FM_ENA_PIN 42                                 //Define pin number for motor controller enable pin
#define FM_DIR_PIN 43                                 //Define pin number for motor controller direction pin
#define FM_PUL_PIN 44                                 //Define pin number for motor controller pulse/step pin

#define CM_ENA_PIN 45                                 //Define pin number for motor controller enable pin
#define CM_DIR_PIN 46                                 //Define pin number for motor controller direction pin
#define CM_PUL_PIN 47                                 //Define pin number for motor controller pulse/step pin

#define CM_HOME_SWITCH_PIN 28                         //Define pin number for homing switch (N.O)
#define CM_LIMIT_SWITCH_MAX_PIN 29                    //Define pin number for maximum R.O.M limit switch
#define CM_LIMIT_SWITCH_MIN_PIN 30                    //Define pin number for minimum R.O.M limit switch

#define PRINTER_PIN 2                                 //Define pin number for print head controller pulse
                                                      //  !!! CAUTION !!! - Pins A0>A3 must be kept free for print head data

#define RED_ANDON_PIN 7                               //Define pin to control andon light
#define YEL_ANDON_PIN 8                               //Define pin to control andon light
#define GRN_ANDON_PIN 9                               //Define pin to control andon light

#define CABLE_DETECTION_PIN 54                        //Define pin which cable detection device is connected (must be ADC pin)

#define PDU_INTLK_PIN 18                              //Define PDU interlock pin (Must be interrupt enabled)
#define MOT_INTLK_PIN 19                              //Define Motor interlock pin (Must be interrupt enabled)

/**********************************************************************************************************
   DEFINE PARAMETERS
**********************************************************************************************************/

#define FM_MAX_SPEED 1000                             //Define maximum motor speed value
#define FM_MAX_ACCEL 1000                             //Define maximum motor acceleration value

#define CM_MAX_SPEED 1000                             //Define maximum motor speed value
#define CM_MAX_ACCEL 1000                             //Define maximum motor acceleration value

#define FM_CIRCUMFERENCE 182.2                        //Define circumference of feed roller
#define FM_STEP_ANGLE 1.8                             //Define step angle of motor  >>SEE NOTE BELOW<<
#define FM_MICROSTEP_SETTING 8                        //Define the microstep setting of the motor controller

#define CM_STEP_ANGLE 1.8                              //Define step angle of motor
#define CM_MICROSTEP_SETTING 1                         //Define the microstep setting of the motor controller >>SEE NOTE BELOW<<
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

#define FM_D2S_FACTOR FM_CIRCUMFERENCE / FM_STEP_ANGLE * FM_MICROSTEP_SETTING                             //Defines the distance to steps factor

#define CM_STEPS_PER_TURN CM_STEP_ANGLE*360                                                               //Calculate number of steps per full turn of motor
#define CM_S2L_FACTOR ((CM_STEPS_PER_TURN * CM_MICROSTEP_SETTING) / CM_SCREW_PITCH) * CM_GEAR_RATIO       //Calculate number of steps per 1mm linear travel of carriage


/**********************************************************************************************************
   DECLARE VARIABLES & CONSTANTS
**********************************************************************************************************/

String cableID;                                       //Declare a string variable to store the cable ID
int cableLength;                                      //Declare an integer variable to store the cable length
int cableGauge;                                       //Declare an integer variable to store the cable gauge
int distance = 0;                                     //Declare variable to store distance feed roller has moved
bool newData = false;                                 //Declare and initialize a boolean flag for new data received
bool paused = false;                                  //Declare and initialize a boolean flag for the paused state
bool gaugeMatch = false;                              //Declare flag to indicate if the cable gauge values match within the range.
bool pduMessagePrinted = false;                       //Declare flag to indicate if PDU interlock message has been sent
bool motorMessagePrinted = false;                     //Declare flag to indicate if motor interlock message has been sent
volatile bool pduInterlock = false;                   //Declare flag to indicate if PDU interlock is engaged
volatile bool motorInterlock = false;                 //Declare flag to indicate if motor interlock is engaged

int CM_homing_pos = 0;                                //Declare global variable for homing position
int cutPosition = 100;                                //Length of travel of linear actuator for cut motor (final position of blade after cutting)
int releasePosition = -350;                           //Distance to move cable in reverse to release from feed rollers

const int PDU_Intlk = PDU_INTLK_PIN;                  //Pin connected to PDU interlock signal
const int Motor_Intlk = MOT_INTLK_PIN;                //Pin connected to Motor interlock signal

/**********************************************************************************************************
   DECLARE OBJECTS
**********************************************************************************************************/

AccelStepper FeedMotor(AccelStepper::DRIVER, FM_PUL_PIN, FM_DIR_PIN);     //Create class for feed motor
AccelStepper CutMotor(AccelStepper::DRIVER, CM_PUL_PIN, CM_DIR_PIN);      //Create class for cut motor

CableIDPrinter printer(PRINTER_PIN);                                      //Create printer class initialize on printer pin


/*────────────────────────────────────────────────────────────────────────────
   CM STARTUP HOMING POSITION
────────────────────────────────────────────────────────────────────────────*/

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


/*────────────────────────────────────────────────────────────────────────────
   CABLE GAUGE CHECK
────────────────────────────────────────────────────────────────────────────*/

void checkGaugeMatch(int cableGauge)                  //Check inserted cable matches gauge declared by MAS application
{
  int potValue = analogRead(CABLE_DETECTION_PIN);     //Read the ADC value (0 to 1023).
   
  int mappedValue = map(potValue, 0, 1023, 2, 25);    // Map the ADC reading to the range 2mm to 25mm.

  if (abs(mappedValue - cableGauge) <= 1)             //Compare the mapped value with cableGauge If the values are within plus or minus 1mm, set gaugeMatch to true, else false
  {
    gaugeMatch = true;
  }
    
  else                                                //Otherwise set the gaugematch flag to false and light yellow andon
  {
    gaugeMatch = false;
    digitalWrite(GRN_ANDON_PIN, LOW);
    digitalWrite(RED_ANDON_PIN, LOW);
    digitalWrite(YEL_ANDON_PIN, HIGH);
  }
}

/*────────────────────────────────────────────────────────────────────────────
   OVERRIDE GAUGE MISMATCH
────────────────────────────────────────────────────────────────────────────*/

void overrideGaugeMatch()                             //Operator override cable gauge mismatch
{
  if (Serial.available() > 0)                         //If data in serial buffer
  {
    String inputString = Serial.readString();         //Read the input string from Serial Monitor.

    inputString.trim();                               //Trim the input string.

    if (inputString == "override")                    //Check if the input string is "override"
    {
      gaugeMatch = true;                              //Manually set gaugeMatch to true.
      digitalWrite(GRN_ANDON_PIN, HIGH);              //Light green andon
      digitalWrite(RED_ANDON_PIN, LOW);
      digitalWrite(YEL_ANDON_PIN, LOW);
    }
  }
}

/*────────────────────────────────────────────────────────────────────────────
   PDU INTERLOCK ISR
────────────────────────────────────────────────────────────────────────────*/

void pduInterlockISR()                              // Interrupt Service Routine for PDU interlock Pin
{
  pduInterlock = digitalRead(PDU_Intlk) == HIGH;
}

/*────────────────────────────────────────────────────────────────────────────
   MOTOR INTERLOCK ISR
────────────────────────────────────────────────────────────────────────────*/

void motorInterlockISR()                           //Interrupt Service Routine for Motor interlock Pin
{
  motorInterlock = digitalRead(Motor_Intlk) == HIGH;
}

/*────────────────────────────────────────────────────────────────────────────
   CHECK PDU INTERLOCK
────────────────────────────────────────────────────────────────────────────*/

void checkAndPrintPduInterlock()                //Check if PDU interlock message has been sent to MAS application
{
  if (pduInterlock && !pduMessagePrinted)       //If PDU interlock flag true and no message sent
  {
    Serial.println("PDU Interlock");            //Send message

    pduMessagePrinted = true;                   //Update message sent flag
    
    digitalWrite(GRN_ANDON_PIN, LOW);
    digitalWrite(RED_ANDON_PIN, HIGH);          //Light red andon
    digitalWrite(YEL_ANDON_PIN, LOW);
  }
  
  else                                          //Otherwise set message sent flag false
  {
    pduMessagePrinted = false;
  }
}

/*────────────────────────────────────────────────────────────────────────────
   CHECK MOTOR INTERLOCK
────────────────────────────────────────────────────────────────────────────*/

void checkAndPrintMotorInterlock()                //Check if motor interlock message has been sent to MAS application
{
  if (motorInterlock && !motorMessagePrinted)     //If motor interlock flag true and no message sent
  {
    Serial.println("Motor Interlock");            //Send message

    motorMessagePrinted = true;                   //Update message sent flag

    digitalWrite(GRN_ANDON_PIN, LOW);
    digitalWrite(RED_ANDON_PIN, HIGH);            //Light red andon
    digitalWrite(YEL_ANDON_PIN, LOW);
  }
  
  else                                            //Otherwise set message sent flag false
  {
    motorMessagePrinted = false;
  }
}

/*────────────────────────────────────────────────────────────────────────────
   READ SERIAL DATA
────────────────────────────────────────────────────────────────────────────*/

void readSerialData()                               //Read cable data and store to relevant variables
{
  if (Serial.available())                           //Check if there is data available to be read from the serial port
  {
    if (!paused && Serial.peek() == '<')            //If the system is not paused and the next character in the serial buffer is '<'
    {
      Serial.read();                                //Read and discard the '<' character
      cableID = Serial.readStringUntil(',');        //Read the string until the next ',' character and store it in the variable cableID
      cableLength = Serial.parseInt();              //Read the next integer value from the serial buffer and store it in the variable cableLength
      cableGauge = Serial.parseInt();               //Read the next integer value from the serial buffer and store it in the variable cableGauge

      if (Serial.read() == '>')                     //Check if the next character in the serial buffer is '>'
      {
        newData = true;                             //Set the newData flag to indicate that new data has been received
      }
    }
    
    else                                            //Otherwise
    {
      handleSerialCommands();                       //Call handle serial commands
    }
  }
}


/*────────────────────────────────────────────────────────────────────────────
   HANDLE SERIAL COMMANDS
────────────────────────────────────────────────────────────────────────────*/

void handleSerialCommands()
{
  String command = Serial.readStringUntil('\n');       //Read the incoming string until a newline character ('\n') is encountered and store it in the variable command
  command.trim();                                      //Remove leading and trailing whitespace characters from the command string

  if (command == "pause" && !paused)                   //If the command is "pause" and the system is not already paused
  {
    paused = true;                                     //Set the paused flag to true

    Serial.println("--  Machine paused  --");          //Send message
    
    digitalWrite(YEL_ANDON_PIN, HIGH);                 //Light yellow andon
    digitalWrite(RED_ANDON_PIN, LOW);
    digitalWrite(GRN_ANDON_PIN, LOW);
  }
  
  else if (command == "resume" && paused)               //If the command is "resume" and the system is currently paused
  {
    paused = false;                                     //Set the paused flag to false to indicate that the system is resumed

    Serial.println("--  Machine resumed --");           //Send message

    digitalWrite(YEL_ANDON_PIN, LOW);
    digitalWrite(RED_ANDON_PIN, LOW);
    digitalWrite(GRN_ANDON_PIN, HIGH);                   //Light green andon
  }
  
  else if (paused)                                       //Otherwise if the system is paused
  {
    Serial.println("\n!!!  System is paused, cannot execute instruction  !!!\n");  //Send message
  }
}


/*────────────────────────────────────────────────────────────────────────────
   PRINT CABLE DATA
────────────────────────────────────────────────────────────────────────────*/

void printCableData()                                  //Echo the cable data to MAS software
{
  if (newData)                                         //If new data is available
  {
    Serial.println("--------------------");            //Print a separator line
    Serial.print("Cable ID: ");                        //Print the label for the cable ID
    Serial.println(cableID);                           //Print the value of the cable ID
    Serial.print("Cable Length: ");                    //Print the label for the cable length
    Serial.println(cableLength);                       //Print the value of the cable length
    Serial.print("Cable Gauge: ");                     //Print the label for the cable gauge
    Serial.println(cableGauge);                        //Print the value of the cable gauge
    Serial.println("--------------------");            //Print a separator line
  }
}


/*────────────────────────────────────────────────────────────────────────────
   MOVE FEED MOTOR
────────────────────────────────────────────────────────────────────────────*/

void moveFeedMotor(int distance)                        //Feed cable and print ID
{
  int steps = map(distance, 0, 100, 0, FM_D2S_FACTOR);  //Map the desired distance to steps

  FeedMotor.enableOutputs();                            //Enable motor outputs
  FeedMotor.setCurrentPosition(0);                      //Set the current motor position to 0
  FeedMotor.moveTo(steps);                              //Move the motor to the calculated number of steps

  while (FeedMotor.isRunning())                         //Continue running the motor until it reaches the target position
  {
    FeedMotor.run();                                    //Execute motor movement
    printer.printCableIDToInkShield(cableID);           //Print the cable ID continuously while motor is in motion
  }

  FeedMotor.disableOutputs();                           //Disable motor outputs
  delay(1000);                                          //Wait 1 second
  FeedMotor.setCurrentPosition(0);                      //Set the current motor position back to 0
}


/*────────────────────────────────────────────────────────────────────────────
   MOVE CUT MOTOR
────────────────────────────────────────────────────────────────────────────*/

void moveCutMotor()
{
  CutMotor.enableOutputs();                             //Enable motor outputs
  CutMotor.moveTo(cutPosition);                         //Move the cut motor to the specified cut position

  while (CutMotor.isRunning())                          //Continue running the cut motor until it reaches the target position
  {
    CutMotor.run();                                     //Execute cut motor movement
  }

  CutMotor.moveTo(CM_homing_pos);                       //Move the cut motor to the homing position (return home)

  while (CutMotor.isRunning())                          //Continue running the cut motor until it reaches the homing position
  {
    CutMotor.run();                                     //Execute cut motor movement
  }

  CutMotor.disableOutputs();                            //Disable motor outputs
  delay(1000);                                          //Wait 1 second
}



/*────────────────────────────────────────────────────────────────────────────
   SETUP
────────────────────────────────────────────────────────────────────────────*/

void setup()
{
  Serial.begin(9600);                                 // Initialize serial communication at 9600 baud rate
  Serial.println("OpenCut Machine Connected");        // Print a connection message to the serial monitor

  pinMode(YEL_ANDON_PIN, OUTPUT);                     //Set pin as output
  pinMode(RED_ANDON_PIN, OUTPUT);                     //Set pin as output
  pinMode(GRN_ANDON_PIN, OUTPUT);                     //Set pin as output
  pinMode(CM_HOME_SWITCH_PIN, INPUT_PULLUP);          //Set pin as input
  pinMode(CM_LIMIT_SWITCH_MAX_PIN, INPUT_PULLUP);     //Set pin as input
  pinMode(CM_LIMIT_SWITCH_MIN_PIN, INPUT_PULLUP);     //Set pin as input

  pinMode(PDU_Intlk, INPUT_PULLUP);                   //Set PDU interlock pin as input
  pinMode(Motor_Intlk, INPUT_PULLUP);                 //Set motor interlock pin as input

  attachInterrupt(digitalPinToInterrupt(PDU_Intlk), pduInterlockISR, CHANGE);       //Attach interupt to ISR
  attachInterrupt(digitalPinToInterrupt(Motor_Intlk), motorInterlockISR, CHANGE);   //Attach interupt to ISR


  digitalWrite(YEL_ANDON_PIN, HIGH);                  //Switch on yellow andon

  FeedMotor.setEnablePin(FM_ENA_PIN);                 //Declare feed motor enable pin [Must be manually declared when using driver type in class]
  FeedMotor.setPinsInverted(false, false, true);      //Invert the logic of the enable pin (step, direction, enable)
  FeedMotor.setMaxSpeed(FM_MAX_SPEED);                //Set speed = steps/second
  FeedMotor.setAcceleration(FM_MAX_ACCEL);            //Set acceleration = steps/(second)^2

  FeedMotor.disableOutputs();                         //Prevent current flow to motor (prevents overheating)


  CM_startup_homing_sequence();                      //Call function for homing cut motor at startup

  Serial.println("Setup Complete");                   //Print to serial monitor

  digitalWrite(GRN_ANDON_PIN, HIGH);                  //Switch on green andon
  digitalWrite(RED_ANDON_PIN, LOW);
  digitalWrite(YEL_ANDON_PIN, LOW);
}

/*────────────────────────────────────────────────────────────────────────────
   MAIN PROGRAM
────────────────────────────────────────────────────────────────────────────*/

void loop()
{
  checkAndPrintPduInterlock();                        //Call PDU Interlock Function
  checkAndPrintMotorInterlock();                      //Call motor Interlock Function
  readSerialData();                                   //Call read serail data function
  printCableData();                                   //Call print cable data function
  checkGaugeMatch(cableGauge);                        //Call check gauge match function

  if (gaugeMatch)                                     //If cable gauge matches
  {
    Serial.println("Gauge OK!");                      //Send message
  }

  else                                                //Otherwise
  {
    Serial.println("WARNING: Gauge Mismatch!");       //Send message
    digitalWrite(YEL_ANDON_PIN, HIGH);                //Light yellow andon
    overrideGaugeMatch();                             //Call override gauge match function
  }

  if (!paused && newData && gaugeMatch)               //If the system is not paused, new data is available, and the gauge matches
  {
    moveFeedMotor(cableLength);                       //Move the feed motor based on the cable length
    moveCutMotor();                                   //Call move cut motor function

    FeedMotor.enableOutputs();                        //Enable motor outputs for the feed motor
    FeedMotor.setCurrentPosition(0);                  //Set the current motor position of the feed motor to 0
    FeedMotor.moveTo(releasePosition);                //Move the feed motor to the release position

    while (FeedMotor.isRunning())                     //Continue running the feed motor until it reaches the release position
    {
      FeedMotor.run();                                //Execute feed motor movement
    }

    FeedMotor.disableOutputs();                       //Disable motor outputs for the feed motor (Prevents overheating)
    delay(1000);                                      //Wait 1 second
    FeedMotor.setCurrentPosition(0);                  //Set the current motor position of the feed motor back to 0

    newData = false;                                  //Reset the newData flag to indicate that the data has been processed
  }
}