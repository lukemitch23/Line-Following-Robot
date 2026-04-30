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

/* Include required header files */


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
	/* Ensure right indicators are LIGHT_OFF */
	Front_Right_Yellow(LIGHT_OFF);
	Back_Right_Yellow(LIGHT_OFF);
	Front_Left_Yellow(set);
	Back_Left_Yellow(set);
}

void LIGHT_CONTROL__Turn_Right(bool set) {
	/* Ensure left inidcators are LIGHT_OFF */
	Front_Left_Yellow(LIGHT_OFF);
	Back_Left_Yellow(LIGHT_OFF);
	Front_Right_Yellow(set);
	Back_Right_Yellow(set);
}

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

void Front_Left_White(bool set) {
	LATAbits.LATA2 = set;
}
void Front_Right_White(bool set) {
	LATAbits.LATA0 = set;
}
void Back_Left_White(bool set) {
	LATEbits.LATE0 = set;
}
void Back_Right_White(bool set) {
	LATAbits.LATA6 = set;
}
void Back_Left_Red(bool set) {
	LATAbits.LATA4 = set;
}
void Back_Right_Red(bool set) {
	LATEbits.LATE1 = set;
}
void Front_Left_Yellow(bool set) {
	LATAbits.LATA3 = set;
}
void Front_Right_Yellow(bool set) {
	LATAbits.LATA1 = set;
}
void Back_Left_Yellow(bool set) {
	LATAbits.LATA5 = set;
}
void Back_Right_Yellow(bool set) {
	LATEbits.LATE2 = set;
}