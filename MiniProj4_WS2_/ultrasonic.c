/*
 * ultrasonic.c
 *
 *  Created on: Oct 15, 2021
 *      Author: Mohamed Ezzat
 */

#include "ultrasonic.h"
#include "icu.h"
#include "gpio.h"
#include "util/delay.h"
#include "common_macros.h"
#include "avr/io.h"

uint8 g_edgeCount = 0;
uint16 g_timeHigh = 0;
uint16 g_timePeriod = 0;
uint16 g_timePeriodPlusHigh = 0;

void Ultrasonic_edgeProcessing(void) {
	g_edgeCount++;
	if (g_edgeCount == 1) {
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		Icu_clearTimerValue();
		/* Detect falling edge */
		Icu_setEdgeDetectionType(FALLING);
	} else if (g_edgeCount == 2) {
		/* Store the High time value */
		g_timeHigh = Icu_getInputCaptureValue();
		Icu_clearTimerValue();
		/* Detect rising edge */
		Icu_setEdgeDetectionType(RISING);
	}
}

void Ultrasonic_init(void) {
	Icu_ConfigType ICU_Config;
	ICU_Config.clock = F_CPU_8;
	ICU_Config.edge = RISING;
	Icu_init(&ICU_Config);
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(PORTB_ID, PIN5_ID, PIN_OUTPUT);
	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_LOW);
}
void Ultrasonic_Trigger(void) {

	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_HIGH);
	_delay_us(20);
	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_LOW);
}

uint16 Ultrasonic_readDistance(void) {
	_delay_ms(60); /* according to datasheet period of trigger plus should be at least 60 ms */
	Ultrasonic_Trigger(); /* send trigger pulse to ultrasonic module */
	while (g_edgeCount < 2);  /* wait to count 2 edges (rising and falling) */
	g_edgeCount=0; /* reset edge count */
	return ((float) g_timeHigh / 58.8);
}
