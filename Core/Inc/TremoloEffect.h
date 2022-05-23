/*
 * TremoloEffect.h
 *
 *  Created on: May 22, 2022
 *      Author: Armin
 */

#ifndef SRC_TREMOLOEFFECT_H_
#define SRC_TREMOLOEFFECT_H_

typedef struct {
	float phase;
	float inverseSampleRate;
	float depth;
	float frequency;
} TremoloEffect;

enum WaveForm { Triangle, Square, SquareSlopedEdges, Sine };

float lfo(float phase, int waveform);

void Tremolo_Init();

uint16_t calculateTremolo(uint16_t in, float volume);

#endif /* SRC_TREMOLOEFFECT_H_ */
