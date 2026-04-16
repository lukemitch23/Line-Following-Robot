/**********************************************************************************************************************************
 *
 *  File name: LIGHT_CONTROL.c
 *  Date: 18/03/2026
 *
 *  Description: C file for the light control function. Function implementation allowing the user to control the headlights as
 *				 well as toggle the reverse lights and the indicators when turning. Public functions allow control of the light
 *				 groups with individual lights controlled by local functions.
 *
**********************************************************************************************************************************/

/* Include header file */
#include "LIGHT_CONTROL.h"

void LIGHT_CONTROL__Init(void){
	/* Initalise all the lights to off */
	Front_Left_White(OFF);
	Front_Right_White(OFF);
	Back_Left_White(OFF);
	Back_Right_White(OFF);
	Back_Left_Red(OFF);
	Back_Right_Red(OFF);
	Front_Left_Yellow(OFF);
	Front_Right_Yellow(OFF);
	Back_Left_Yellow(OFF);
	Back_Right_Yellow(OFF);
}

void LIGHT_CONTROL__Head_Lights(bool set){
	Front_Left_White(set);
	Front_Right_White(set);
	Back_Left_White(set);
	Back_Right_White(set);
}



void LIGHT_CONTROL__Reverse_Lights(bool set) {
	/* Assume correct input and set the red lights to the choice */
	Back_Left_Red(set);
	Back_Right_Red(set);
}

void LIGHT_CONTROL__Turn_Left(bool set) {
	/* Ensure right indicators are off */
	Front_Right_Yellow(OFF);
	Back_Right_Yellow(OFF);
	Front_Left_Yellow(set);
	Front_Right_Yellow(set);
}

void LIGHT_CONTROL__Turn_Right(bool set) {
	/* Ensure left inidcators are off */
	Front_Left_Yellow(OFF);
	Back_Left_Yellow(OFF);
	Front_Right_Yellow(set);
	Front_Right_Yellow(set);
}

void LIGHT_CONTROL__All_Off(void){
	/* Set all lights to off */
	Front_Left_White(OFF);
	Front_Right_White(OFF);
	Back_Left_White(OFF);
	Back_Right_White(OFF);
	Back_Left_Red(OFF);
	Back_Right_Red(OFF);
	Front_Left_Yellow(OFF);
	Front_Right_Yellow(OFF);
	Back_Left_Yellow(OFF);
	Back_Right_Yellow(OFF);
}

void Front_Left_White(bool set);
void Front_Right_White(bool set);
void Back_Left_White(bool set);
void Back_Right_White(bool set);
void Back_Left_Red(bool set);
void Back_Right_Red(bool set);
void Front_Left_Yellow(bool set);
void Front_Right_Yellow(bool set);
void Back_Left_Yellow(bool set);
void Back_Right_Yellow(bool set);