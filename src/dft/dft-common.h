#pragma once

struct note_pitch {
    float freq;
    char name[3];
    unsigned char octave;
};

typedef struct note_pitch note_pitch_t;

note_pitch_t *create_pitch_array(float base64);
