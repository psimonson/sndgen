#ifndef SNDFORMAT_H
#define SNDFORMAT_H

#include "synth.h"
#include <stdint.h>

typedef struct {
    SynthNote* notes;
    uint32_t note_count;
} Track;

typedef struct {
    Track* tracks;
    uint32_t track_count;
} Song;

void snd_save_song(const char* filename, const Song* song);
Song snd_load_song(const char* filename);
void snd_free_song(Song* song);

#endif // SNDFORMAT_H

