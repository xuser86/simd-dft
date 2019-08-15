#include <stdio.h>
#include <stdlib.h>

#include "../../src/input/decode_audio_file.h"
 
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

    return 0;
}
