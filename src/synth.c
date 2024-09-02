#include "synth.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define TWO_PI 6.283185307179586476925286766559

static float generate_waveform(Waveform waveform, float phase) {
    switch (waveform) {
        case WAVE_SINE:
            return sinf(phase);
        case WAVE_SQUARE:
            return phase < M_PI ? 1.0f : -1.0f;
        case WAVE_TRIANGLE:
            return 2.0f * fabsf(2.0f * (phase / TWO_PI) - 1.0f) - 1.0f;
        case WAVE_SAWTOOTH:
            return 2.0f * (phase / TWO_PI) - 1.0f;
        default:
            return 0.0f;
    }
}

void synth_generate(SynthNote* note, SynthBuffer* buffer) {
    uint32_t sample_count = (uint32_t)(note->duration * note->sample_rate);
    buffer->samples = (float*)malloc(sample_count * sizeof(float));
    buffer->sample_count = sample_count;

    float phase = 0.0f;
    float phase_increment = TWO_PI * note->frequency / note->sample_rate;

    for (uint32_t i = 0; i < sample_count; i++) {
        buffer->samples[i] = note->amplitude * generate_waveform(note->waveform, phase);
        phase += phase_increment;
        if (phase >= TWO_PI) {
            phase -= TWO_PI;
        }
    }
}

void synth_free_buffer(SynthBuffer* buffer) {
    free(buffer->samples);
    buffer->samples = NULL;
    buffer->sample_count = 0;
}

