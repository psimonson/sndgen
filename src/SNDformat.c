#include "SNDformat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void snd_save_song(const char* filename, const Song* song) {
    FILE* file = fopen(filename, "wb");
    if (!file) return;

    fwrite(&song->track_count, sizeof(uint32_t), 1, file);
    for (uint32_t i = 0; i < song->track_count; i++) {
        fwrite(&song->tracks[i].note_count, sizeof(uint32_t), 1, file);
        fwrite(song->tracks[i].notes, sizeof(SynthNote), song->tracks[i].note_count, file);
    }

    fclose(file);
}

Song snd_load_song(const char* filename) {
    Song song = {0};

    FILE* file = fopen(filename, "rb");
    if (!file) return song;

    fread(&song.track_count, sizeof(uint32_t), 1, file);
    song.tracks = (Track*)malloc(song.track_count * sizeof(Track));

    for (uint32_t i = 0; i < song.track_count; i++) {
        fread(&song.tracks[i].note_count, sizeof(uint32_t), 1, file);
        song.tracks[i].notes = (SynthNote*)malloc(song.tracks[i].note_count * sizeof(SynthNote));
        fread(song.tracks[i].notes, sizeof(SynthNote), song.tracks[i].note_count, file);
    }

    fclose(file);
    return song;
}

void snd_free_song(Song* song) {
    for (uint32_t i = 0; i < song->track_count; i++) {
        free(song->tracks[i].notes);
    }
    free(song->tracks);
    song->track_count = 0;
    song->tracks = NULL;
}

