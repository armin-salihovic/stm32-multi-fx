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
	int sampleRate;
} DelayEffect;

void Delay_Init(int sampleRate);

uint16_t Delay_Process(uint16_t in);

void Delay_Set_Params(float delayLength, float feedback);

void Delay_Free();

#endif /* INC_DELAYEFFECT_H_ */
