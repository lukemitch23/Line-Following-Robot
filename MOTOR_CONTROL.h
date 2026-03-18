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
 *  Function name: MOTOR_CONTROL__FORWARDS
 *  Description: Drives both wheels forwards.
 *
 *  Inputs: None
 *  Outputs: None
 *
**********************************************************************************************************************************/
void MOTOR_CONTROL__FORWARDS(void) {};

/**********************************************************************************************************************************
 *
 *  Function name: MOTOR_CONTROL__BACKWARDS
 *  Description: Drives both wheels backwards
 *
 *  Inputs: None
 *  Outputs: None
 *
**********************************************************************************************************************************/
void MOTOR_CONTROL__BACKWARDS(void) {};

/**********************************************************************************************************************************
 *
 *  Function name: MOTOR_CONTROL__GENTLE_LEFT
 *  Description: Drives the right motor forwards to turn the robot left
 *
 *  Inputs: None
 *  Outputs: None
 *
**********************************************************************************************************************************/
void MOTOR_CONTROL__GENTLE_LEFT(void) {};

/**********************************************************************************************************************************
 *
 *  Function name: MOTOR_CONTROL__GENTLE_RIGHT
 *  Description: Drives the left motor forwards to turn the robot right
 *
 *  Inputs: None
 *  Outputs: None
 *
**********************************************************************************************************************************/
void MOTOR_CONTROL__GENTLE_RIGHT(void) {};

/**********************************************************************************************************************************
 *
 *  Function name: MOTOR_CONTROL__SHARP_LEFT
 *  Description: Drives the right motor forwards and the left motor backwards to create a sharp left turn
 *
 *  Inputs: None
 *  Outputs: None
 *
**********************************************************************************************************************************/
void MOTOR_CONTROL__SHARP_LEFT(void) {};

/**********************************************************************************************************************************
 *
 *  Function name: MOTOR_CONTROL__SHARP_RIGHT
 *  Description: Drives the left motor forwards and the right motor backwards to create a sharp turn
 *
 *  Inputs: None
 *  Outputs: None
 *
**********************************************************************************************************************************/
void MOTOR_CONTROL__SHARP_RIGHT(void) {};