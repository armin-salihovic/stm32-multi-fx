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
	int sample_rate;
} DelayEffect;

void Delay_Init(int sample_rate);

uint16_t Delay_Process(uint16_t in);

void Delay_Set_Params(float delayLength, float feedback);

#endif /* INC_DELAYEFFECT_H_ */
