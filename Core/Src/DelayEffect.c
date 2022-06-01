/*
 * DelayEffect.c
 *
 *  Created on: May 22, 2022
 *      Author: Armin
 */

#include <stdlib.h>
#include <stdint.h>
#include "DelayEffect.h"
#define DATA_SIZE 128

// the size of the entire buffer for both adc and dac
#define BUFFER_SIZE 256

DelayEffect* delay = NULL;

void Delay_Init(int sample_rate) {
	if(delay != NULL) return;

	delay = malloc(sizeof(DelayEffect));
	delay->sample_rate = sample_rate;
	delay->delayBufferLength = 2*sample_rate;
	delay->delayLength = 0.75f;
	delay->delayWritePtr = 0;
	delay->delayReadPtr = 0;
	delay->delayData = (uint16_t*) malloc(delay->delayBufferLength * sizeof(uint16_t));

	for (int i = 0; i < delay->delayBufferLength; ++i) {
		delay->delayData[i] = 0;
	}

	delay->feedback = 0.75f;
	delay->dryMix = 1;
	delay->wetMix = 1;
}

uint16_t Delay_Process(uint16_t in) {
	uint16_t out = 0;

	out = (delay->dryMix * in + delay->wetMix *delay->delayData[delay->delayReadPtr]);

	delay->delayData[delay->delayWritePtr] = in + (delay->delayData[delay->delayReadPtr]*delay->feedback);

	if(++delay->delayReadPtr >= delay->delayBufferLength)
		delay->delayReadPtr = 0;

	if(++delay->delayWritePtr >= delay->delayBufferLength)
		delay->delayWritePtr = 0;

	return out;
}

void Delay_Set_Params(float delayLength, float feedback) {
	if(delayLength < 0.05) delayLength = 0.05;

	delayLength *= 2.0f;

	if(delayLength - 0.1 > delay->delayLength - 0.01  || delayLength + 0.1 < delay->delayLength + 0.01) {
		delay->delayLength = delayLength;
		delay->delayReadPtr = (int)(delay->delayWritePtr - (delay->delayLength * delay->sample_rate) + delay->delayBufferLength) % delay->delayBufferLength;
	}

	if(feedback > 0.8) feedback = 0.8;

	if(feedback - 0.1 > delay->feedback - 0.01 || feedback + 0.1 < delay->feedback + 0.01) {
		delay->feedback = feedback;
	}
}

void Delay_Free() {
	if(delay != NULL) {
		free(delay->delayData);
		free(delay);

		delay = NULL;
	}
}

