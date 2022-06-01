/*
 * OnePoleLP.c
 *
 * Code inspired by: https://github.com/SpotlightKid/ykchorus
 *
 *  Created on: May 24, 2022
 *      Author: Armin
 */

#include <OnePoleLP.h>

OnePoleLP onePoleLP;

void OnePoleLP_Init() {
	onePoleLP.lastOutput = onePoleLP.inputs = onePoleLP.outputs = 0.0f;
}

void Tick(float *sample, float cutoff) {
	float p = (cutoff * 0.98f) * (cutoff * 0.98f) * (cutoff * 0.98f) * (cutoff * 0.98f);
	onePoleLP.outputs = (1.0f - p) * (*sample) + p * onePoleLP.outputs;
	*sample = onePoleLP.outputs;
}
