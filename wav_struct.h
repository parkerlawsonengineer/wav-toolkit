#ifndef WAV_STRUCT_INCLUDE
#define WAV_STRUCT_INCLUDE
#include "stdint.h"



typedef struct {

    uint8_t is_valid_wav; //set in read_header(), true if header was read successfully

    //=================WAV FILE HEADER==================

    //RIFF chunk
    uint32_t file_size; //total size of file (minus 8 bytes, this value only counts everything after the RIFF chunk) 

    //fmt  chunk
    uint32_t format_size; //size of chunk for format
    uint16_t format_type; //audio format
    uint16_t num_channels; //number of audio channels
    uint32_t sample_rate; //samples per second
    uint32_t byte_rate; //bytes per second: (sample_rate * sample_size * num_channels) / 8
    uint16_t block_align; //number of bytes per "block" (a block contains 1 sample for each channel)
    uint16_t sample_size; //bits per sample

    //data chunk
    uint32_t data_size; //number of bytes of data
    //==================================================

    uint32_t data_index; //offset for beginning of data in file

} WAV;

#endif