/*=============================================================================================================
*
 * File name: SENSOR.c
 * Date: 18/03/2026
 * Author: 24066795
 *
 * Function: 5 IR line array sensor interface, initalises the sensor ports, reads the sensor and processes
 *			 the output. Controls the motor and the lights depending on the sensor output.
=============================================================================================================*/

/* Include the objects header file */
#include "SENSOR.h"

/* Include required header files */
#include "CONFIGURATION.h"
#include "COMMON.h"
#include "MOTOR_CONTROL.h"
#include "LIGHT_CONTROL.h"

/* Define the sensor reading array */
bool Sensor_Value_g[5] = {0,0,0,0,0};

/**************************************************************************************************************
 * Function name: SENSOR__Init
 * Purpose: Initialise the senosr ports. Sets the ports to digital and initialises only the required ports
 *			to inputs.
**************************************************************************************************************/

void SENSOR__Init(void) {
	/* Initalise PORT C and PORT D to digital */
    ANSELD = 0;
    ANSELC = 0;

	/* Initalise the ports to input*/
	TRISDbits.TRISD7 = 1;
    TRISDbits.TRISD6 = 1;
    TRISDbits.TRISD5 = 1;
    TRISDbits.TRISD4 = 1;
	TRISCbits.TRISC7 = 1;
}

/**************************************************************************************************************
 * Function name: SENSOR__Read_Sensor
 * Purpose: Loop through the sensor_value array, reading the value from the line sensor array from the
 *			correct pin for each index.
**************************************************************************************************************/

void SENSOR__Read_Sensor(void) {
	/* Loop through all indicies of the array */
	for (int index = 0; index < 5; index++) {
		/* Switch to write to the correct pin for the index
		 * Inverting the input of each pin to make 1 equal to black
		 */
		switch (index) {
			case 0:
				Sensor_Value_g[index] = !RD7;
				break;
			case 1:
				Sensor_Value_g[index] = !PORTDbits.RD6;
			    break;
			case 2:
				Sensor_Value_g[index] = !PORTDbits.RD5;
			    break;
			case 3:
				Sensor_Value_g[index] = !PORTDbits.RD4;
				break;
			case 4:
				Sensor_Value_g[index] = !PORTCbits.RC7;
				break;
			/* Include default condition to catch any error values */
			default:
				Sensor_Value_g[index] = 0;
		}
	}
}

/**************************************************************************************************************
 * Function name: SENSOR__Process_Sensor
 * Purpose: Branching statements relating to individual sensors value to control the operation of the robot
**************************************************************************************************************/

void SENSOR__Process_Sensor(void) {

	/* If the middle sensor is black then we can drive forwards
	 * At the same time, illuminate the headlights and disable the rear lights
	 */
	if (Sensor_Value_g[2]) {
        MOTOR_CONTROL__Forwards();
	} else if (Sensor_Value_g[3] || Sensor_Value_g[4]) {
		LIGHT_CONTROL__Turn_Left(1);
		MOTOR_CONTROL__Left();
	} else if (Sensor_Value_g[1] || Sensor_Value_g[0]) {
		LIGHT_CONTROL__Turn_Right(1);
		MOTOR_CONTROL__Right();
	} else if (!Sensor_Value_g[0] && !Sensor_Value_g[1] &&
		!Sensor_Value_g[2] && !Sensor_Value_g[3] && !Sensor_Value_g[4]){
        MOTOR_CONTROL__Right();
	}

	/* If the right sensors are black then turn left to bring the LFR back
	 * onto the line
	 */
	

	/* If the left sensors are black then turn right to bring the LFR back
	 * onto the line
	 */
	

	/* If all sensors are white then stop the robot and turn the
	 * rear lights on as the line has been lost
	 */
	
}

