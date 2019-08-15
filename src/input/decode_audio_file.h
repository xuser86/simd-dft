#pragma once

int decode_audio_file(const char* path, int *sample_rate, float** data, int* size);
