#include <stdio.h>
#include <string.h>
#include "../../src/dft/dft-common.h"

const char *names[] = {
    "C0", "C#0", "D0", "D#0", "E0", "F0", "F#0", "G0", "G#0", "A0", "H0", "B0", 
    "C1", "C#1", "D1", "D#1", "E1", "F1", "F#1", "G1", "G#1", "A1", "H1", "B1", 
    "C2", "C#2", "D2", "D#2", "E2", "F2", "F#2", "G2", "G#2", "A2", "H2", "B2", 
    "C3", "C#3", "D3", "D#3", "E3", "F3", "F#3", "G3", "G#3", "A3", "H3", "B3", 
    "C4", "C#4", "D4", "D#4", "E4", "F4", "F#4", "G4", "G#4", "A4", "H4", "B4", 
    "C5", "C#5", "D5", "D#5", "E5", "F5", "F#5", "G5", "G#5", "A5", "H5", "B5", 
    "C6", "C#6", "D6", "D#6", "E6", "F6", "F#6", "G6", "G#6", "A6", "H6", "B6", 
    "C7", "C#7", "D7", "D#7", "E7", "F7", "F#7", "G7", "G#7", "A7", "H7", "B7", 
    "C8", "C#8", "D8", "D#8", "E8", "F8", "F#8", "G8", "G#8", "A8", "H8", "B8", 
    "C9", "C#9", "D9", "D#9", "E9", "F9", "F#9", "G9", "G#9", "A9", "H9", "B9", 
    "C10", "C#10", "D10", "D#10", "E10", "F10", 
    "F#10", "G10", "G#10", "A10", "H10", "B10"    
};

const float freqs[] = {
    16.351599, 17.323914, 18.354048, 19.445436, 20.601723, 21.826765, 
    23.124651, 24.499714, 25.956543, 27.500000, 29.135235, 30.867706, 
    32.703197, 34.647827, 36.708096, 38.890873, 41.203445, 43.653530, 
    46.249302, 48.999428, 51.913086, 55.000000, 58.270470, 61.735413, 
    65.406395, 69.295654, 73.416191, 77.781746, 82.406891, 87.307060, 
    92.498604, 97.998856, 103.826172, 110.000000, 116.540939, 123.470825, 
    130.812790, 138.591309, 146.832382, 155.563492, 164.813782, 174.614120, 
    184.997208, 195.997711, 207.652344, 220.000000, 233.081879, 246.941650, 
    261.625580, 277.182617, 293.664764, 311.126984, 329.627563, 349.228241, 
    369.994415, 391.995422, 415.304688, 440.000000, 466.163757, 493.883301, 
    523.251160, 554.365234, 587.329529, 622.253967, 659.255127, 698.456482, 
    739.988831, 783.990845, 830.609375, 880.000000, 932.327515, 987.766602, 
    1046.502319, 1108.730469, 1174.659058, 1244.507935, 1318.510254, 1396.912964, 
    1479.977661, 1567.981689, 1661.218750, 1760.000000, 1864.655029, 1975.533203, 
    2093.004639, 2217.460938, 2349.318115, 2489.015869, 2637.020508, 2793.825928, 
    2959.955322, 3135.963379, 3322.437500, 3520.000000, 3729.310059, 3951.066406, 
    4186.009277, 4434.921875, 4698.636230, 4978.031738, 5274.041016, 5587.651855, 
    5919.910645, 6271.926758, 6644.875000, 7040.000000, 7458.620117, 7902.132812, 
    8372.018555, 8869.843750, 9397.272461, 9956.063477, 10548.082031, 11175.303711, 
    11839.821289, 12543.853516, 13289.750000, 14080.000000, 14917.240234, 15804.265625, 
    16744.037109, 17739.687500, 18794.544922, 19912.126953, 21096.164062, 22350.607422, 
    23679.642578, 25087.707031, 26579.500000, 28160.000000, 29834.480469, 31608.531250
};

int main() {
    note_pitch_t *pitch_array = create_pitch_array(440.0f);
    
    char strbuf[6];
    for(int i = 0; i < 11 * 12; i++) {
        printf(
            "%d) %.2f, %s%d\n", 
            i, 
            pitch_array[i].freq, 
            pitch_array[i].name,
            pitch_array[i].octave  
        );
        snprintf(strbuf, 5, "%s%d", pitch_array[i].name, pitch_array[i].octave);
        if (pitch_array[i].freq != freqs[i]) {
            printf("%f != %f\n", pitch_array[i].freq, freqs[i]);
            return -1;
        }
        
        if (strncmp(strbuf, names[i], 5) != 0) {
            printf("%s != %s\n", strbuf, names[i]);
            return -2;
        }
    }
    
    return 0;
}