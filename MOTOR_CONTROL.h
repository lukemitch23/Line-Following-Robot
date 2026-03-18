/**********************************************************************************************************************************
*
 *  File name: MOTOR_CONTROL.h
 *  Date: 18/03/2026
 *
 *  Description: Header file for the motor control file including the relevent function prototypes.
 *
**********************************************************************************************************************************/

/* Add includes here */

/**********************************************************************************************************************************
 *
 *  Function name: MOTOR_CONTROL__Init
 *  Description: Initalise the motors at the start of the program
 *
 *  Inputs: None
 *  Outputs: None
 *
**********************************************************************************************************************************/
void MOTOR_CONTROL__Init(void) {};

/**********************************************************************************************************************************
 *
 *  Function name: MOTOR_CONTROL__Forwards
 *  Description: Drives both wheels forwards.
 *
 *  Inputs: None
 *  Outputs: None
 *
**********************************************************************************************************************************/
void MOTOR_CONTROL__Forwards(void) {};

/**********************************************************************************************************************************
 *
 *  Function name: MOTOR_CONTROL__Backwards
 *  Description: Drives both wheels backwards
 *
 *  Inputs: None
 *  Outputs: None
 *
**********************************************************************************************************************************/
void MOTOR_CONTROL__Backwards(void) {};

/**********************************************************************************************************************************
 *
 *  Function name: MOTOR_CONTROL__Gentle_Left
 *  Description: Drives the right motor forwards to turn the robot left
 *
 *  Inputs: None
 *  Outputs: None
 *
**********************************************************************************************************************************/
void MOTOR_CONTROL__Gentle_Left(void) {};

/**********************************************************************************************************************************
 *
 *  Function name: MOTOR_CONTROL__Gentle_Right
 *  Description: Drives the left motor forwards to turn the robot right
 *
 *  Inputs: None
 *  Outputs: None
 *
**********************************************************************************************************************************/
void MOTOR_CONTROL__Gentle_Right(void) {};

/**********************************************************************************************************************************
 *
 *  Function name: MOTOR_CONTROL__Sharp_Left
 *  Description: Drives the right motor forwards and the left motor backwards to create a sharp left turn
 *
 *  Inputs: None
 *  Outputs: None
 *
**********************************************************************************************************************************/
void MOTOR_CONTROL__Sharp_Left(void) {};

/**********************************************************************************************************************************
 *
 *  Function name: MOTOR_CONTROL__Sharp_Right
 *  Description: Drives the left motor forwards and the right motor backwards to create a sharp turn
 *
 *  Inputs: None
 *  Outputs: None
 *
**********************************************************************************************************************************/
void MOTOR_CONTROL__Sharp_Right(void) {};

/**********************************************************************************************************************************
 *
 *  Function name: MOTOR_CONTROL__Stop
 *  Description: Stop both motors to stop the robot
 *
 *  Inputs: None
 *  Outputs: None
 *
**********************************************************************************************************************************/
void MOTOR_CONTROL__Stop(void) {};