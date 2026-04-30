/**********************************************************************************************************************************
 *
 *  File name: LIGHT_CONTROL.h
 *  Date: 18/03/2026
 *
 *  Description: Header file for the light control function. Function headers that will allow the user to control the
 *				 robots lights. Also defining the ON and OFF constants.
 *
**********************************************************************************************************************************/

#include "COMMON.h"

/* Define constants for on and off */

/*
 latA 0 - FRW
 * 1 - FRY
 * 2 - FLW
 * 3 - FLY
 * 4 - RLR
 * 5 - RLY
 * 6 -
 * 7 - RRW
 *
 * LAT E
 * 0 - RLW
 * 1 - RRR
 * 2 - RRY
 */

/***************************************************************
 * Function declarations
***************************************************************/

void LIGHT_CONTROL__Init(void);
void LIGHT_CONTROL__Head_Lights(bool set);
void LIGHT_CONTROL__Reverse_Lights(bool set);
void LIGHT_CONTROL__Turn_Left(bool set);
void LIGHT_CONTROL__Turn_Right(bool set);
void LIGHT_CONTROL__All_Off(void);

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