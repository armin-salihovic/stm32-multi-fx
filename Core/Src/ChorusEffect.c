/*
 * YKchorus->c
 *
 * Code inspired by: https://github.com/SpotlightKid/ykchorus
 *
 *  Created on: May 24, 2022
 *      Author: Armin
 */

#include <ChorusEffect.h>
#include <stdlib.h>
#include <math.h>
#include <OnePoleLP.h>

ChorusEffect* chorus = NULL;

void Chorus_Init(int sampleRate) {
	if(chorus != NULL) return;

	chorus = malloc(sizeof(ChorusEffect));
	chorus->phase = 1.0f;
	chorus->rate = 1.0f;
	chorus->sampleRate = sampleRate;
	chorus->delayTime = 7.0f;
	chorus->z1 = 0.0f;
	chorus->sign = 0;
	chorus->lfoPhase = chorus->phase * 2.0f - 1.0f;
	chorus->lfoStepSize = (4.0f * chorus->rate / chorus->sampleRate);
	chorus->lfoSign = 1.0f;

	// Compute required buffer size for desired delay and allocate it
	// Add extra point to aid in interpolation later
	chorus->delayLineLength = ((int)floorf(chorus->delayTime * sampleRate * 0.001f) * 2);
	chorus->delayLineStart = malloc(chorus->delayLineLength * sizeof(float));

	// Set up pointers for delay line
	chorus->delayLineEnd = chorus->delayLineStart + chorus->delayLineLength;
	chorus->writePtr = chorus->delayLineStart;

	// Zero out the buffer (silence)
	do {
		*chorus->writePtr = 0.0f;
	}
	while (++chorus->writePtr < chorus->delayLineEnd);

	// Set read pointer to end of delayline. Setting it to the end
	// ensures the interpolation below works correctly to produce
	// the first non-zero sample.
	chorus->writePtr = chorus->delayLineStart + chorus->delayLineLength -1;
	chorus->delayLineOutput = 0.0f;
	OnePoleLP_Init();
}

float Chorus_LFO() {
        if (chorus->lfoPhase >= 1.0f)
        {
        	chorus->lfoSign = -1.0f;
        }
        else if (chorus->lfoPhase <= -1.0f)
        {
        	chorus->lfoSign = +1.0f;
        }
        chorus->lfoPhase += chorus->lfoStepSize * chorus->lfoSign;
        return chorus->lfoPhase;
    }

float Chorus_Process(float sample) {
	// Get delay time
	chorus->offset = (Chorus_LFO() * 0.3f + 0.4f) * chorus->delayTime * chorus->sampleRate * 0.001f;
	int offset = (int)floorf(chorus->offset);

	// Compute the largest read pointer based on the offset.  If ptr
	// is before the first delayline location, wrap around end point

	chorus->ptr = chorus->writePtr - offset;

	if (chorus->ptr < chorus->delayLineStart)
		chorus->ptr += chorus->delayLineLength;

	chorus->ptr2 = chorus->ptr - 1;
	if (chorus->ptr2 < chorus->delayLineStart)
		chorus->ptr2 += chorus->delayLineLength;

	chorus->frac = chorus->offset - offset;
	chorus->delayLineOutput = *chorus->ptr2 + *chorus->ptr * (1 - chorus->frac) - (1 - chorus->frac) * chorus->z1;
	chorus->z1 = chorus->delayLineOutput;

	// Low pass
	Tick(&chorus->delayLineOutput, 0.95f);

	// Write the input sample and any feedback to delayline
	*chorus->writePtr = sample;

	// Increment buffer index and wrap if necesary
	if (++chorus->writePtr >= chorus->delayLineEnd) {
		chorus->writePtr = chorus->delayLineStart;
	}
	return chorus->delayLineOutput;
}

void Chorus_Set_Params(float rate) {
	if(rate - 0.1 > chorus->rate - 0.01  || rate + 0.1 < chorus->rate + 0.01) {
		chorus->rate = rate;
		chorus->lfoStepSize = (4.0f * chorus->rate / chorus->sampleRate);
	}
}

void Chorus_Free() {
	if(chorus != NULL) {
		free(chorus->delayLineStart);
		free(chorus);
		chorus = NULL;
	}
}
