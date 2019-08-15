#include <stdio.h>
#include <stdlib.h>

#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>

#include "decode_audio_file.h"

int decode_audio_file(const char* path, int *sample_rate, float** data, int* size) {
    av_register_all();
    
    AVFormatContext *format = avformat_alloc_context();
    if (avformat_open_input(&format, path, NULL, NULL) != 0) {
        fprintf(stderr, "Could not open file '%s'\n", path);
        return -1;
    }
    if (avformat_find_stream_info(format, NULL) < 0) {
        fprintf(stderr, "Could not retrive stream info from file '%s'\n", path);
        return -1;
    }
    
    int stream_index = -1;
    for (int i = 0; i < format->nb_streams; i++) {
        if (format->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO) {
            stream_index = i;
            printf("Found audio strem at index %d\n", i);
            //printf("With number frames %ld\n", format->streams[i]->nb_frames);
            //printf("Duration %ld\n", format->duration);
            break;
        }
    }
    if (stream_index == -1) {
        fprintf(stderr, "Could not retrive audio stream from file '%s'\n", path);
        return -1;
    }
    AVStream *stream = format->streams[stream_index];
    
    AVCodecContext *codec = stream->codec;
    if (avcodec_open2(codec, avcodec_find_decoder(codec->codec_id), NULL) < 0) {
        fprintf(stderr, "Failed to open decoder for stream #%u in file '%s'\n", 
                stream_index, path);
        return -1;
    } else {
        printf("Sample rate %d\n", codec->sample_rate);
        printf("Channel count %d\n", codec->channels);
        printf("Sample format %s\n", av_get_sample_fmt_name(codec->sample_fmt));
    }

    *sample_rate = codec->sample_rate;
    
    // prepare resampler
    struct SwrContext* swr = swr_alloc();
    av_opt_set_int(swr, "in_channel_count",  codec->channels, 0);
    av_opt_set_int(swr, "out_channel_count", 1, 0);
    av_opt_set_int(swr, "in_channel_layout",  codec->channel_layout, 0);
    av_opt_set_int(swr, "out_channel_layout", AV_CH_LAYOUT_MONO, 0);
    /*av_opt_set_int(swr, "in_sample_rate", codec->sample_rate, 0);
    av_opt_set_int(swr, "out_sample_rate", codec->sample_rate, 0);*/
    av_opt_set_sample_fmt(swr, "in_sample_fmt",  codec->sample_fmt, 0);
    av_opt_set_sample_fmt(swr, "out_sample_fmt", AV_SAMPLE_FMT_FLT,  0);
    swr_init(swr);
    if (!swr_is_initialized(swr)) {
        fprintf(stderr, "Resampler has not been properly initialized\n");
        return -1;
    }

    AVPacket packet;
    av_init_packet(&packet);
    AVFrame *frame = av_frame_alloc();
    if (!frame) {
        fprintf(stderr, "Error allocating the frame\n");
        return -1;
    }
    
    *data = NULL;
    *size = 0;
    int all_frame_count = 0;
    long all_sample_count = 0;
    while (av_read_frame(format, &packet) >= 0) {
        int gotFrame;
        if (avcodec_decode_audio4(codec, frame, &gotFrame, &packet) < 0) {
            break;
        }
        if (!gotFrame) {
            continue;
        }
        /*
         process frame
         */
        all_frame_count += frame->nb_samples;
        all_sample_count++;

        // resample frames
        float* buffer;
        av_samples_alloc((uint8_t**) &buffer, NULL, 1, frame->nb_samples, AV_SAMPLE_FMT_FLT, 0);
        int frame_count = swr_convert(swr, (uint8_t**) &buffer, frame->nb_samples, (const uint8_t**) frame->data, frame->nb_samples);

        // append resampled frames to data
        *data = (float*) realloc(*data, (*size + frame->nb_samples) * sizeof(float));
        memcpy(*data + *size, buffer, frame_count * sizeof(float));
        *size += frame_count;
    }
    
    printf("Read %d frames\n", all_frame_count);
    printf("Read %ld samples\n", all_sample_count);
    
    av_frame_free(&frame);
    avcodec_close(codec);
    avformat_free_context(format);
    
    return 0;
}


