/*
 * ultrasonic.h
 *
 *  Created on: Oct 15, 2021
 *      Author: Mohamed Ezzat
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#include "std_types.h"



uint16 Ultrasonic_readDistance(void);
void Ultrasonic_Trigger(void);
void Ultrasonic_init(void);
void Ultrasonic_edgeProcessing(void);


#endif /* ULTRASONIC_H_ */
