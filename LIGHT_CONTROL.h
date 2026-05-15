/*=============================================================================================================
*
 * File name: LIGHT_CONTROL.h
 * Date: 18/03/2026
 * Author: 24066795
 *
 * Function: Controls all the lights on the LFR.
=============================================================================================================*/

/**************************************************************************************************************
 *
 * Declare public functions
 *
**************************************************************************************************************/

void LIGHT_CONTROL__Init(void);
void LIGHT_CONTROL__Head_Lights(bool set);
void LIGHT_CONTROL__Reverse_Lights(bool set);
void LIGHT_CONTROL__Turn_Left(bool set);
void LIGHT_CONTROL__Turn_Right(bool set);
void LIGHT_CONTROL__All_Off(void);

/**************************************************************************************************************
 *
 * Declare local functions
 *
**************************************************************************************************************/
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