/*
 * main.c
 *
 *  Created on: Oct 18, 2023
 *      Author: Hp
 */


#include "ultrasonic.h"
#include "lcd.h"
#include "gpio.h"
#include "common_macros.h"
#include "std_types.h"
#include "icu.h"
#include <avr/io.h>

uint16 g_dist=0;

int main(){

	Ultrasonic_init();//intializing Ultrasonic driver
	LCD_init();//intializing lcd driver
	LCD_displayStringRowColumn(1,2,"distance = ");
	SREG |= (1<<7);//enabling interrupts



	while(1){
		g_dist=Ultrasonic_readDistance();//getting the distance value using ultrasonic driver
		LCD_moveCursor(1,13); // moving cursor to point after the = to display the distance
		LCD_intgerToString(g_dist);//displaying distance

		/*
		 * to fix the issue of unwanted character of being displayed on lcd while
         * the temp goes from 3 decimals "113" to 2 decimals "49" or even 1 decimal "8"
         */
		LCD_displayCharacter(' ');
	}
}
