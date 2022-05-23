/*
 * DelayEffect.h
 *
 *  Created on: May 22, 2022
 *      Author: Armin
 */

#ifndef INC_DELAYEFFECT_H_
#define INC_DELAYEFFECT_H_

typedef struct {
	uint16_t* delayData;
	int delayWritePtr;
	int delayReadPtr;
	float delayLength;
	int delayBufferLength;
	float feedback;
	float dryMix;
	float wetMix;
} DelayEffect;

void Delay_Init();

uint16_t Calculate_Delay_Sample(uint16_t in);

#endif /* INC_DELAYEFFECT_H_ */
