#include "synth.h"
#include "SNDformat.h"
#include <stdio.h>
#include <stdlib.h>

#define NOTE_C4  261.63f
#define NOTE_D4  293.66f
#define NOTE_E4  329.63f
#define NOTE_F4  349.23f
#define NOTE_G4  392.00f
#define NOTE_A4  440.00f
#define NOTE_B4  493.88f
#define NOTE_C5  523.25f

#define DEFAULT_AMPLITUDE 0.5f
#define DEFAULT_SAMPLE_RATE 44100.0f

void add_note_to_track(Track* track, Waveform waveform, float frequency, float duration) {
    track->notes = realloc(track->notes, (track->note_count + 1) * sizeof(SynthNote));
    track->notes[track->note_count].waveform = waveform;
    track->notes[track->note_count].frequency = frequency;
    track->notes[track->note_count].amplitude = DEFAULT_AMPLITUDE;
    track->notes[track->note_count].duration = duration;
    track->notes[track->note_count].sample_rate = DEFAULT_SAMPLE_RATE;
    track->note_count++;
}

int main() {
    Track melody = { .notes = NULL, .note_count = 0 };

    // Simplified "Trails" melody line
    add_note_to_track(&melody, WAVE_SINE, NOTE_A4, 0.5f);
    add_note_to_track(&melody, WAVE_SINE, NOTE_B4, 0.5f);
    add_note_to_track(&melody, WAVE_SINE, NOTE_C5, 0.5f);
    add_note_to_track(&melody, WAVE_SINE, NOTE_B4, 0.5f);
    add_note_to_track(&melody, WAVE_SINE, NOTE_A4, 0.5f);
    add_note_to_track(&melody, WAVE_SINE, NOTE_G4, 0.5f);
    add_note_to_track(&melody, WAVE_SINE, NOTE_F4, 0.5f);
    add_note_to_track(&melody, WAVE_SINE, NOTE_E4, 0.5f);
    add_note_to_track(&melody, WAVE_SINE, NOTE_F4, 0.5f);
    add_note_to_track(&melody, WAVE_SINE, NOTE_G4, 0.5f);
    add_note_to_track(&melody, WAVE_SINE, NOTE_A4, 0.5f);
    add_note_to_track(&melody, WAVE_SINE, NOTE_G4, 0.5f);

    // Repeat or add more notes to complete the melody...

    Song song = { .tracks = malloc(1 * sizeof(Track)), .track_count = 1 };
    song.tracks[0] = melody;

    // Save the song to a file (optional)
    snd_save_song("cave_story_trails.snd", &song);

    // Synthesize each note in the loaded song and write to stdout
    for (uint32_t i = 0; i < song.track_count; i++) {
        Track* track = &song.tracks[i];
        for (uint32_t j = 0; j < track->note_count; j++) {
            SynthBuffer buffer;
            synth_generate(&track->notes[j], &buffer);

            // Convert the floating-point samples to 16-bit signed PCM and write to stdout
            for (uint32_t k = 0; k < buffer.sample_count; k++) {
                int16_t sample = (int16_t)(buffer.samples[k] * 32767);
                fwrite(&sample, sizeof(int16_t), 1, stdout);
            }

            synth_free_buffer(&buffer);
        }
    }

    snd_free_song(&song);

    return 0;
}

