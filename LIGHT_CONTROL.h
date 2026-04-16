/**********************************************************************************************************************************
 *
 *  File name: LIGHT_CONTROL.h
 *  Date: 18/03/2026
 *
 *  Description: Header file for the light control function. Function headers that will allow the user to control the
 *				 robots lights. Also defining the ON and OFF constants.
 *
**********************************************************************************************************************************/

#include <stdbool.h>

/* Define constants for on and off */
const bool ON = 1;
const bool OFF = 0;

/**********************************************************************************************************************************
*
*	Light Connections:
*		Lights on port A (0-7) (Pins 2-7,13-14) & port E (0-2)(Pins 8-10)
*		Port A:
*			0 -
*			1 -
*			2 -
*			3 -
*			4 -
*			5 -
*			6 -
*			7 -
*
*		Port E:
*			0 -
* 			1 -
*			2 - Spare
*
**********************************************************************************************************************************/

/**********************************************************************************************************************************
 *
 *  Function name: LIGHT_CONTROL__Init
 *
 *  Input: None
 *  Outputs: None
 *
 *  Usage: Initialised the lights all to off
 *
**********************************************************************************************************************************/
void LIGHT_CONTROL__Init(void);

/**********************************************************************************************************************************
 *
 *  Function name: LIGHT_CONTROL__Head_Lights
 *
 *  Input: bool set
 *  Outputs: None
 *
 *  Usage: Turn the headlights on or off depending on user input
 *
**********************************************************************************************************************************/
void LIGHT_CONTROL__Head_Lights(bool set);

/**********************************************************************************************************************************
 *
 *  Function name: LIGHT_CONTROL__Reverse_Lights
 *
 *  Input: bool set
 *  Outputs: None
 *
 *  Usage: Turn the reversing lights on or off depending on user input
 *
**********************************************************************************************************************************/
void LIGHT_CONTROL__Reverse_Lights(bool set);

/**********************************************************************************************************************************
 *
 *  Function name: LIGHT_CONTROL__Turn_Left
 *
 *  Input: bool set
 *  Outputs: None
 *
 *  Usage: Turn the left indicator on or off when turning for calling from an interrupt
 *
**********************************************************************************************************************************/
void LIGHT_CONTROL__Turn_Left(bool set);

/**********************************************************************************************************************************
 *
 *  Function name: LIGHT_CONTROL__Turn_Right
 *
 *  Input: bool set
 *  Outputs: None
 *
 *  Usage: Turn the right indicator on or off when turning for calling from an interrupt
 *
**********************************************************************************************************************************/
void LIGHT_CONTROL__Turn_Right(bool set);

/**********************************************************************************************************************************
 *
 *  Function name: LIGHT_CONTROL__All_Off
 *
 *  Input: None
 *  Outputs: None
 *
 *  Usage: Set all lights off
 *
**********************************************************************************************************************************/
void LIGHT_CONTROL__All_Off(void);

/**********************************************************************************************************************************
 *
 *  Function name: Front_Left_White
 *
 *  Input: None
 *  Outputs: None
 *
 *  Usage: Set the light on or off based on the user input
 *
**********************************************************************************************************************************/
void Front_Left_White(bool set);

/**********************************************************************************************************************************
 *
 *  Function name: Front_Right_White
 *
 *  Input: None
 *  Outputs: None
 *
 *  Usage: Set the light on or off based on the user input
 *
**********************************************************************************************************************************/
void Front_Right_White(bool set);

/**********************************************************************************************************************************
 *
 *  Function name: Back_Left_White
 *
 *  Input: None
 *  Outputs: None
 *
 *  Usage: Set the light on or off based on the user input
 *
**********************************************************************************************************************************/
void Back_Left_White(bool set);

/**********************************************************************************************************************************
 *
 *  Function name: Back_Right_White
 *
 *  Input: None
 *  Outputs: None
 *
 *  Usage: Set the light on or off based on the user input
 *
**********************************************************************************************************************************/
void Back_Right_White(bool set);

/**********************************************************************************************************************************
 *
 *  Function name: Back_Left_Red
 *
 *  Input: None
 *  Outputs: None
 *
 *  Usage: Set the light on or off based on the user input
 *
**********************************************************************************************************************************/
void Back_Left_Red(bool set);

/**********************************************************************************************************************************
 *
 *  Function name: Back_Right_Red
 *
 *  Input: None
 *  Outputs: None
 *
 *  Usage: Set the light on or off based on the user input
 *
**********************************************************************************************************************************/
void Back_Right_Red(bool set);

/**********************************************************************************************************************************
 *
 *  Function name: Front_Left_Yellow
 *
 *  Input: None
 *  Outputs: None
 *
 *  Usage: Set the light on or off based on the user input
 *
**********************************************************************************************************************************/
void Front_Left_Yellow(bool set);

/**********************************************************************************************************************************
 *
 *  Function name: Front_Right_Yellow
 *
 *  Input: None
 *  Outputs: None
 *
 *  Usage: Set the light on or off based on the user input
 *
**********************************************************************************************************************************/
void Front_Right_Yellow(bool set);

/**********************************************************************************************************************************
 *
 *  Function name: Back_Left_Yellow
 *
 *  Input: None
 *  Outputs: None
 *
 *  Usage: Set the light on or off based on the user input
 *
**********************************************************************************************************************************/
void Back_Left_Yellow(bool set);

/**********************************************************************************************************************************
 *
 *  Function name: Back_Right_Yellow
 *
 *  Input: None
 *  Outputs: None
 *
 *  Usage: Set the light on or off based on the user input
 *
**********************************************************************************************************************************/
void Back_Right_Yellow(bool set);