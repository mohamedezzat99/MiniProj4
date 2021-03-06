/*
 * Proj.c
 *
 *  Created on: Oct 15, 2021
 *      Author: Mohamed Ezzat
 */
#include "ultrasonic.h"
#include "lcd.h"
#include "avr/interrupt.h"
#include "util/delay.h"
int main() {
	uint16 distance;
	LCD_init();
	Ultrasonic_init();
	LCD_displayString("Distance = ");
	sei();

	while (1) {
		distance = Ultrasonic_readDistance();
		LCD_moveCursor(0, 11);
		if (distance >= 100) {
			LCD_intgerToString(distance);
		} else {
			LCD_intgerToString(distance); /* In case the digital value is three or two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}
		LCD_displayString("cm");
	}
}
