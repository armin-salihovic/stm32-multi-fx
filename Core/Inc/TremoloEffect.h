/*
 * TremoloEffect.h
 *
 *  Created on: May 22, 2022
 *      Author: Armin
 */

#ifndef SRC_TREMOLOEFFECT_H_
#define SRC_TREMOLOEFFECT_H_

enum WaveForm { Triangle, Square, SquareSlopedEdges, Sine };

typedef struct {
	float phase;
	float inverseSampleRate;
	float depth;
	float frequency;
	int waveform;
} TremoloEffect;

float lfo(float phase, int waveform);

void Tremolo_Init(int sample_rate);

float Tremolo_Process(float in, float depth, float frequency);

#endif /* SRC_TREMOLOEFFECT_H_ */
