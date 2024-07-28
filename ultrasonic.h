/*
 * ultrasonic.h
 *
 *  Created on: Oct 16, 2023
 *      Author: Hp
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"
#include "gpio.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ULTRASONIC_TRIGGER_PORT_ID		PORTB_ID
#define ULTRASONIC_TRIGGER_PIN_ID		PIN5_ID

#define ULTRASONIC_ECHO_PORT_ID		PORTD_ID
#define ULTRASONIC_ECHO_PIN_ID		PIN6_ID


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void Ultrasonic_init(void);

void Ultrasonic_Trigger(void);

uint16 Ultrasonic_readDistance(void);

void Ultrasonic_edgeProcessing(void);



#endif /* ULTRASONIC_H_ */
