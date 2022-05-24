#include "print.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void print_header(WAV wav) {

    if (!wav.is_valid_wav) {
        #ifdef DEBUG
            fprintf(stderr, "WAV file is not valid\n");
        #endif

        return;
        
    }


    print_header_riff(wav);
    print_header_fmt(wav);
    print_header_data(wav);
    
}

void print_header_riff(WAV wav) {

    if (!wav.is_valid_wav) {
        #ifdef DEBUG
            fprintf(stderr, "WAV file is not valid\n");
        #endif

        return;
        
    }

    fprintf(stdout, "RIFF chunk:\n");
    fprintf(stdout, "file_size: %u\n", wav.file_size);


}

void print_header_fmt(WAV wav) {

    if (!wav.is_valid_wav) {
        #ifdef DEBUG
            fprintf(stderr, "WAV file is not valid\n");
        #endif

        return;
        
    }

    fprintf(stdout, "fmt chunk\n");
    fprintf(stdout, "format_size: %u\n", wav.format_size);
    fprintf(stdout, "format_type: %u\n", wav.format_type);
    fprintf(stdout, "num_channels: %u\n", wav.num_channels);
    fprintf(stdout, "sample_rate: %u\n", wav.sample_rate);
    fprintf(stdout, "byte_rate: %u\n", wav.byte_rate);
    fprintf(stdout, "block_align: %u\n", wav.block_align);
    fprintf(stdout, "sample_size: %u\n", wav.sample_size);

}

void print_header_data(WAV wav) {

    if (!wav.is_valid_wav) {
        #ifdef DEBUG
            fprintf(stderr, "WAV file is not valid\n");
        #endif

        return;
        
    }

    fprintf(stdout, "data chunk\n");
    fprintf(stdout, "data_size: %u\n", wav.data_size);

}


