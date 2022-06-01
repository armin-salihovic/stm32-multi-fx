/*
 * OnePoleLP.h
 *
 * Code inspired by: https://github.com/SpotlightKid/ykchorus
 *
 *  Created on: May 24, 2022
 *      Author: Armin
 */

#ifndef INC_ONEPOLELP_H_
#define INC_ONEPOLELP_H_

typedef struct {
	float inputs, outputs, lastOutput;
} OnePoleLP;

void OnePoleLP_Init();

void Tick(float *sample, float cutoff);

#endif /* INC_ONEPOLELP_H_ */
