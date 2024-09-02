#ifndef SYNTH_H
#define SYNTH_H

#include <stdint.h>

typedef enum {
    WAVE_SINE,
    WAVE_SQUARE,
    WAVE_TRIANGLE,
    WAVE_SAWTOOTH
} Waveform;

typedef struct {
    Waveform waveform;
    float frequency;
    float amplitude;
    float duration;  // in seconds
    float sample_rate;
} SynthNote;

typedef struct {
    float* samples;
    uint32_t sample_count;
} SynthBuffer;

void synth_generate(SynthNote* note, SynthBuffer* buffer);
void synth_free_buffer(SynthBuffer* buffer);

#endif // SYNTH_H

