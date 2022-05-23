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
	delay.delayLength = 0.75;
	delay.delayWritePtr = 0;
	delay.delayReadPtr = (int)(delay.delayWritePtr - (delay.delayLength * SAMPLE_RATE) + delay.delayBufferLength) % delay.delayBufferLength;
	delay.delayData = (uint16_t*) malloc(delay.delayBufferLength * sizeof(uint16_t));
	delay.feedback = 0.5;
	delay.dryMix = 1;
	delay.wetMix = 0.85;
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

