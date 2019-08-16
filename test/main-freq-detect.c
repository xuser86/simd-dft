#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

#include "../src/input/decode_audio_file.h"
#include "../src/dft/dft-common.h"
 
int main(int argc, const char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Put filepath as argument\n");
        return -1;
    }
    
    int sample_rate;
    float *data;
    int size;
    if (decode_audio_file(argv[1], &sample_rate, &data, &size) != 0) {
        return -1;
    }
    
    printf("in main\nsize: %d\nsample_rate: %d\n", size, sample_rate);

    note_pitch_t *pitch_array = create_pitch_array(440.0f);

    for(int i = 0; i < 11 * 12; i++) {
        printf(
            "%4s%02d, %8.2f",  
            pitch_array[i].name,
            pitch_array[i].octave,
            pitch_array[i].freq  
        );
        float complex val = simple_single_harmonic(
            data, size, sample_rate, pitch_array[i].freq);

        printf(" -> %.f\n", creal(val), cimag(val), cabs(val));
    }

    return 0;
}
