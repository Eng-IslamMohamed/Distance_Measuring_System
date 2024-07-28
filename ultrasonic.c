/*
 * ultrasonic.c
 *
 *  Created on: Oct 16, 2023
 *      Author: Hp
 */


#include "ultrasonic.h"
#include "std_types.h"
#include "common_macros.h"
#include "gpio.h"
#include "icu.h"
#include <util/delay.h>


static uint8 g_edgeCount=0;
static uint16 g_timeHigh=0;
static float32 g_distance=0;


void Ultrasonic_init(void){
	/*
	 * Initializing ULTRASONIC by:
	 * initializing ICU
	 * setting the call back function
	 * setting trigger pin direction
	 */

	ICU_ConfigType ICU_Configurations={F_CPU_8,RAISING};
	ICU_init(&ICU_Configurations);
	ICU_setCallBack(Ultrasonic_edgeProcessing);

	GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,PIN_OUTPUT);
}

void Ultrasonic_Trigger(void){

	// ULTRASONIC needs to be supplied with 10us pulse to the trigger input to start ranging
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,LOGIC_HIGH);
	_delay_ms(10);
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,LOGIC_LOW);
}

uint16 Ultrasonic_readDistance(void){
	//sending the trigger pulse
	Ultrasonic_Trigger();
	//starting measurements by the ICU right after triggering the pulse
	if(g_edgeCount==2){
		g_edgeCount = 0;

		g_distance = (uint16)((float32)(g_timeHigh)*0.0170068027210884);

	}

	return g_distance;


}


void Ultrasonic_edgeProcessing(void){
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		ICU_clearTimerValue();
		/* Detect falling edge */
		ICU_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{
		/* Store the High time value */
		g_timeHigh = ICU_getInputCaptureValue();

		/* Detect rising edge */
		ICU_setEdgeDetectionType(RAISING);
	}


}
