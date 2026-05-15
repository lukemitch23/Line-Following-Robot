/*=============================================================================================================
*
 * File name: LIGHT_CONTROL.c
 * Date: 18/03/2026
 * Author: 24066795
 *
 * Function: Controls all the lights on the LFR.
=============================================================================================================*/

/* Include required header files */
#include "COMMON.h"

/* Include objects header file */
#include "LIGHT_CONTROL.h"



/**************************************************************************************************************
 * Function name: LIGHT_CONTROL__Init
 * Purpose: Initialises all light control ports. Sets PORT A and PORT E to digital outputs, then sets
 *          all lights to LIGHT_OFF to ensure a known state on startup.
**************************************************************************************************************/
void LIGHT_CONTROL__Init(void){
	/* Set the ports for output and digital */
    TRISA = 0; // Output
    ANSELA = 0; // Digital
	TRISE = 0;
	ANSELE = 0;

	/* Initalise all the lights to LIGHT_OFF */
	Front_Left_White(LIGHT_OFF);
	Front_Right_White(LIGHT_OFF);
	Back_Left_White(LIGHT_OFF);
	Back_Right_White(LIGHT_OFF);
	Back_Left_Red(LIGHT_OFF);
	Back_Right_Red(LIGHT_OFF);
	Front_Left_Yellow(LIGHT_OFF);
	Front_Right_Yellow(LIGHT_OFF);
	Back_Left_Yellow(LIGHT_OFF);
	Back_Right_Yellow(LIGHT_OFF);
}

/**************************************************************************************************************
 * Function name: LIGHT_CONTROL__Head_Lights
 * Purpose: Sets all four white headlights (front and rear) to the given state. Used when the LFR
 *          is moving forwards along the line.
**************************************************************************************************************/
void LIGHT_CONTROL__Head_Lights(bool set){
	Front_Left_White(set);
	Front_Right_White(set);
	Back_Left_White(set);
	Back_Right_White(set);
}

/**************************************************************************************************************
 * Function name: LIGHT_CONTROL__Reverse_Lights
 * Purpose: Sets both rear red lights to the given state. Illuminated when the LFR has lost the line
 *          to indicate the robot has stopped.
**************************************************************************************************************/
void LIGHT_CONTROL__Reverse_Lights(bool set) {
	/* Assume correct input and set the red lights to the choice */
	Back_Left_Red(set);
	Back_Right_Red(set);
}

/**************************************************************************************************************
 * Function name: LIGHT_CONTROL__Turn_Left
 * Purpose: Activates the left-side yellow indicators and ensures the right-side indicators are off.
 *          Called when the LFR detects the line to the right and steers left to correct its heading.
**************************************************************************************************************/
void LIGHT_CONTROL__Turn_Left(bool set) {
	/* Ensure right indicators are LIGHT_OFF */
	Front_Right_Yellow(LIGHT_OFF);
	Back_Right_Yellow(LIGHT_OFF);
	Front_Left_Yellow(set);
	Back_Left_Yellow(set);
}

/**************************************************************************************************************
 * Function name: LIGHT_CONTROL__Turn_Right
 * Purpose: Activates the right-side yellow indicators and ensures the left-side indicators are off.
 *          Called when the LFR detects the line to the left and steers right to correct its heading.
**************************************************************************************************************/
void LIGHT_CONTROL__Turn_Right(bool set) {
	/* Ensure left inidcators are LIGHT_OFF */
	Front_Left_Yellow(LIGHT_OFF);
	Back_Left_Yellow(LIGHT_OFF);
	Front_Right_Yellow(set);
	Back_Right_Yellow(set);
}

/**************************************************************************************************************
 * Function name: LIGHT_CONTROL__All_Off
 * Purpose: Sets every light on the LFR to LIGHT_OFF. Used to return all lights to a safe, known
 *          state, for example during shutdown or re-initialisation.
**************************************************************************************************************/
void LIGHT_CONTROL__All_Off(void){
	/* Set all lights to LIGHT_OFF */
	Front_Left_White(LIGHT_OFF);
	Front_Right_White(LIGHT_OFF);
	Back_Left_White(LIGHT_OFF);
	Back_Right_White(LIGHT_OFF);
	Back_Left_Red(LIGHT_OFF);
	Back_Right_Red(LIGHT_OFF);
	Front_Left_Yellow(LIGHT_OFF);
	Front_Right_Yellow(LIGHT_OFF);
	Back_Left_Yellow(LIGHT_OFF);
	Back_Right_Yellow(LIGHT_OFF);
}

/**************************************************************************************************************
 * Function name: Front_Left_White
 * Purpose: Sets the front-left white light to the given state via LATA2.
**************************************************************************************************************/
void Front_Left_White(bool set) {
	LATAbits.LATA2 = set;
}

/**************************************************************************************************************
 * Function name: Front_Right_White
 * Purpose: Sets the front-right white light to the given state via LATA0.
**************************************************************************************************************/
void Front_Right_White(bool set) {
	LATAbits.LATA0 = set;
}

/**************************************************************************************************************
 * Function name: Back_Left_White
 * Purpose: Sets the rear-left white light to the given state via LATE0.
**************************************************************************************************************/
void Back_Left_White(bool set) {
	LATEbits.LATE0 = set;
}

/**************************************************************************************************************
 * Function name: Back_Right_White
 * Purpose: Sets the rear-right white light to the given state via LATA6.
**************************************************************************************************************/
void Back_Right_White(bool set) {
	LATAbits.LATA6 = set;
}

/**************************************************************************************************************
 * Function name: Back_Left_Red
 * Purpose: Sets the rear-left red light to the given state via LATA4.
**************************************************************************************************************/
void Back_Left_Red(bool set) {
	LATAbits.LATA4 = set;
}

/**************************************************************************************************************
 * Function name: Back_Right_Red
 * Purpose: Sets the rear-right red light to the given state via LATE1.
**************************************************************************************************************/
void Back_Right_Red(bool set) {
	LATEbits.LATE1 = set;
}

/**************************************************************************************************************
 * Function name: Front_Left_Yellow
 * Purpose: Sets the front-left yellow indicator to the given state via LATA3.
**************************************************************************************************************/
void Front_Left_Yellow(bool set) {
	LATAbits.LATA3 = set;
}

/**************************************************************************************************************
 * Function name: Front_Right_Yellow
 * Purpose: Sets the front-right yellow indicator to the given state via LATA1.
**************************************************************************************************************/
void Front_Right_Yellow(bool set) {
	LATAbits.LATA1 = set;
}

/**************************************************************************************************************
 * Function name: Back_Left_Yellow
 * Purpose: Sets the rear-left yellow indicator to the given state via LATA5.
**************************************************************************************************************/
void Back_Left_Yellow(bool set) {
	LATAbits.LATA5 = set;
}

/**************************************************************************************************************
 * Function name: Back_Right_Yellow
 * Purpose: Sets the rear-right yellow indicator to the given state via LATE2.
**************************************************************************************************************/
void Back_Right_Yellow(bool set) {
	LATEbits.LATE2 = set;
}
