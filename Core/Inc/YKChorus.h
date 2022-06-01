/*
 * YKChorus.h
 *
 * Code inspired by: https://github.com/SpotlightKid/ykchorus
 *
 *  Created on: May 24, 2022
 *      Author: Armin
 */

#ifndef INC_YKCHORUS_H_
#define INC_YKCHORUS_H_

typedef struct {
	float *delayLineStart;
	float *delayLineEnd;
	float *writePtr;

	int delayLineLength;
	float rate;
	float delayLineOutput;

	float sampleRate;
	float delayTime;

	// Runtime variables
	float offset, diff, frac, *ptr, *ptr2;

	int readPos;

	float z1;
	float mult, sign;

	// lfo
	float lfoPhase, lfoStepSize, lfoSign;

	float phase;
} YKChorus;

void YKChorus_Init(int sampleRate, float phase, float rate, float delayTime);

float Next_LFO();

float YKChorus_Process(float sample);

void YKChorus_Set_Params(float rate, float depth);

void YKChorus_Free();

#endif /* INC_YKCHORUS_H_ */
