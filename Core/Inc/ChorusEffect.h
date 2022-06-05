/*
 * ChorusEffect.h
 *
 * Code inspired by: https://github.com/SpotlightKid/ykchorus
 *
 *  Created on: May 24, 2022
 *      Author: Armin
 */

#ifndef INC_CHORUSEFFECT_H_
#define INC_CHORUSEFFECT_H_

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
} ChorusEffect;

void Chorus_Init(int sampleRate);

float Chorus_LFO();

float Chorus_Process(float sample);

void Chorus_Set_Params(float rate);

void Chorus_Free();

#endif /* INC_CHORUSEFFECT_H_ */
