#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "dft-common.h"

note_pitch_t *create_pitch_array(float baseA4) {
    const char *pitch_names[] = {
        "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "H", "B"
    };
    
    note_pitch_t * pitch_array = 
        (note_pitch_t *) malloc(11 * 12 * sizeof(note_pitch_t));
    
    for (int i = 0; i <= 11 * 12; i++) {
        pitch_array[i].freq = pow(2, (i - 57.0)/12.0) * baseA4;
        pitch_array[i].octave = (int8_t)floor(i / 12);
        strncpy(pitch_array[i].name, pitch_names[i % 12], 2);
    }
    
    return pitch_array;
}

int *check_tones(const int sample_rate, const float* data, const int size) {
    return 0;
}
