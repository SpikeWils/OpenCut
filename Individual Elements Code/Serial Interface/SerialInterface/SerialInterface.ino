/*****************************************************
   LIBRARY INCLUDES
*****************************************************/

#include <Arduino.h>  // Import the Arduino library for easy microcontroller programming


/*****************************************************
   DECLARE VARIABLES & CONSTANTS
*****************************************************/

String cableID;                                       // Declare a string variable to store the cable ID
int cableLength;                                      // Declare an integer variable to store the cable length
int cableGauge;                                       // Declare an integer variable to store the cable gauge
boolean newData = false;                              // Declare and initialize a boolean flag for new data received
boolean paused = false;                               // Declare and initialize a boolean flag for the paused state

/*──────────────────────────────────────
   SETUP
──────────────────────────────────────*/

void setup()
{
  Serial.begin(9600);                                 // Initialize serial communication at 9600 baud rate
  Serial.println("OpenCut Machine Connected");        // Print a connection message to the serial monitor
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