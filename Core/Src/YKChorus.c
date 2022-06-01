/*
 * YKchorus->c
 *
 * Code inspired by: https://github.com/SpotlightKid/ykchorus
 *
 *  Created on: May 24, 2022
 *      Author: Armin
 */

#include <stdlib.h>
#include <math.h>
#include <YKchorus.h>
#include <OnePoleLP.h>

YKChorus* chorus = NULL;

void YKChorus_Init(int sampleRate, float phase, float rate, float delayTime) {
	if(chorus != NULL) return;

	chorus = malloc(sizeof(YKChorus));
	chorus->phase = phase;
	chorus->rate = rate;
	chorus->sampleRate = sampleRate;
	chorus->delayTime = delayTime;
	chorus->z1 = 0.0f;
	chorus->sign = 0;
	chorus->lfoPhase = phase * 2.0f - 1.0f;
	chorus->lfoStepSize = (4.0f * chorus->rate / chorus->sampleRate);
	chorus->lfoSign = 1.0f;

	// Compute required buffer size for desired delay and allocate it
	// Add extra point to aid in interpolation later
//	chorus->delayLineLength = ((int)floorf(delayTime * sampleRate * 0.001f) * 2);
	chorus->delayLineLength = 2*sampleRate;
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

float Next_LFO() {
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

float YKChorus_Process(float sample) {
	// Get delay time
	chorus->offset = (Next_LFO() * 0.3f + 0.4f) * chorus->delayTime * chorus->sampleRate * 0.001f;

	// Compute the largest read pointer based on the offset.  If ptr
	// is before the first delayline location, wrap around end point

	chorus->ptr = chorus->writePtr - (int)floorf(chorus->offset);
//	chorus->ptr = chorus->writePtr - 5;
//	return sample;

	if (chorus->ptr < chorus->delayLineStart)
		chorus->ptr += chorus->delayLineLength;

	chorus->ptr2 = chorus->ptr - 1;
	if (chorus->ptr2 < chorus->delayLineStart)
		chorus->ptr2 += chorus->delayLineLength;

	chorus->frac = chorus->offset - (int)floorf(chorus->offset);
//	chorus->frac = chorus->offset - 5;
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

void YKChorus_Set_Params(float rate, float phase) {
	if(rate - 0.1 > chorus->rate - 0.01  || rate + 0.1 < chorus->rate + 0.01) {
		chorus->rate = rate;
		chorus->lfoStepSize = (4.0f * chorus->rate / chorus->sampleRate);
	}


//	if(phase - 0.1 > chorus->phase - 0.01  || phase + 0.1 < chorus->phase + 0.01) {
//		chorus->phase = phase;
//		chorus->lfoPhase = phase * 2.0f - 1.0f;
//	}

}

void YKChorus_Free() {
	if(chorus != NULL) {
		free(chorus->delayLineStart);
		free(chorus);
		chorus = NULL;
	}
}
