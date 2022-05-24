/*
 * DelayEffect.c
 *
 *  Created on: May 22, 2022
 *      Author: Armin
 */
#include <stdint.h>
#include "DelayEffect.h"
#include <stdlib.h>
#define DATA_SIZE 128

// the size of the entire buffer for both adc and dac
#define BUFFER_SIZE 256
#define SAMPLE_RATE 96000
#define PI 3.14159265359

DelayEffect delay;

void Delay_Init() {
	delay.delayBufferLength = 2*SAMPLE_RATE;
	delay.delayLength = 1.5f;
	delay.delayWritePtr = 0;
	delay.delayReadPtr = (int)(delay.delayWritePtr - (delay.delayLength * SAMPLE_RATE) + delay.delayBufferLength) % delay.delayBufferLength;
	delay.delayData = (uint16_t*) malloc(delay.delayBufferLength * sizeof(uint16_t));
	delay.feedback = 0.75f;
	delay.dryMix = 1;
	delay.wetMix = 1;
}

uint16_t calculateDelay(uint16_t in) {
	uint16_t out = 0;

	out = (delay.dryMix * in + delay.wetMix *delay.delayData[delay.delayReadPtr]);

	delay.delayData[delay.delayWritePtr] = in + (delay.delayData[delay.delayReadPtr]*delay.feedback);

	if(++delay.delayReadPtr >= delay.delayBufferLength)
		delay.delayReadPtr = 0;

	if(++delay.delayWritePtr >= delay.delayBufferLength)
		delay.delayWritePtr = 0;

	return out;
}

void Delay_Set_Params(float delayLength, float feedback) {
	if(delayLength > delay.delayLength - 0.1 - 0.001 || delayLength + 0.1 < delay.delayLength - 0.001) {
		delay.delayLength = delayLength;
		delay.delayReadPtr = (int)(delay.delayWritePtr - (delay.delayLength * SAMPLE_RATE) + delay.delayBufferLength) % delay.delayBufferLength;
	}

	if(feedback > 0.8) feedback = 0.8;

	if(feedback > delay.feedback - 0.1 - 0.001 || feedback + 0.1 < delay.feedback - 0.001) {
		delay.feedback = feedback;
	}


}

