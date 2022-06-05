/*
 * TremoloEffect.h
 *
 *  Created on: May 22, 2022
 *      Author: Armin
 */

#ifndef SRC_TREMOLOEFFECT_H_
#define SRC_TREMOLOEFFECT_H_

enum WaveForm { Triangle, Square, Sine };

typedef struct {
	float phase;
	float inverseSampleRate;
	float depth;
	float frequency;
	int waveform;
} TremoloEffect;

float Tremolo_LFO(float phase, int waveform);

void Tremolo_Init(int sampleRate);

float Tremolo_Process(float in, float depth, float frequency);

void Tremolo_Set_Waveform(int waveform);

void Tremolo_Free();

#endif /* SRC_TREMOLOEFFECT_H_ */
