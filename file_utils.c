#include "file_utils.h"
#include "wav_struct.h"
#include <stdlib.h>
#include <string.h>


//=========General Purpose Functions=============

FILE* open_file(char* filepath) {

    #ifdef DEBUG
        fprintf(stdout, "Attempting to open file: %s\n", filepath);
    #endif

    FILE* opened_file = fopen(filepath, "rb");

    if (opened_file == NULL) {
        fprintf(stderr, "File could not be opened.\n");
        return NULL;
    } else {
        #ifdef DEBUG
            fprintf(stdout, "File opened.\n");
        #endif
        return opened_file;
    }

}









//=========Header Functions======================

uint8_t read_riff_chunk(FILE* file, WAV* wav) {

    uint32_t file_size;

    #ifdef DEBUG
    fprintf(stdout, "Attempting to read RIFF chunk:\n");
    #endif

    uint32_t index;
    uint8_t found_chunk = find_chunk_header(file, "RIFF", &index);

    if (found_chunk) {
        //read in file size (4 bytes)
        fseek(file, index + 4, SEEK_SET);
        fread(&file_size, 4, 1, file);

        #ifdef DEBUG
            fprintf(stdout, "file_size: %u\n", file_size);
        #endif

        wav->file_size = file_size;

        return 1;

    } else {

        return 0;

    }


}

uint8_t read_fmt_chunk(FILE* file, WAV* wav) {

    uint32_t format_size; //size of chunk for format
    uint16_t format_type; //audio format
    uint16_t num_channels; //number of audio channels
    uint32_t sample_rate; //samples per second
    uint32_t byte_rate; //bytes per second: (sample_rate * sample_size * num_channels) / 8
    uint16_t block_align; //number of bytes per "block" (a block contains 1 sample for each channel)
    uint16_t sample_size; //bits per sample

    #ifdef DEBUG
    fprintf(stdout, "Attempting to read fmt  chunk:\n");
    #endif

    uint32_t index;
    uint8_t found_chunk = find_chunk_header(file, "fmt ", &index);

    if (found_chunk) {

        //move to location of chunk data
        fseek(file, index + 4, SEEK_SET);

        //read in format size (4 bytes)
        fread(&format_size, 4, 1, file);

        #ifdef DEBUG
            fprintf(stdout, "format_size: %u\n", format_size);
        #endif

        //read in format type (2 bytes)
        fread(&format_type, 2, 1, file);

        #ifdef DEBUG
            fprintf(stdout, "format_type: %u\n", format_type);
        #endif

        //read in number of channels (2 bytes)
        fread(&num_channels, 2, 1, file);

        #ifdef DEBUG
            fprintf(stdout, "num_channels: %u\n", num_channels);
        #endif

        //read in sample rate (4 bytes)
        fread(&sample_rate, 4, 1, file);

        #ifdef DEBUG
            fprintf(stdout, "sample_rate: %u\n", sample_rate);
        #endif

        //read in byte rate (4 bytes)
        fread(&byte_rate, 4, 1, file);

        #ifdef DEBUG
            fprintf(stdout, "byte_rate: %u\n", byte_rate);
        #endif

        //read in block align (2 bytes)
        fread(&block_align, 2, 1, file);

        #ifdef DEBUG
            fprintf(stdout, "block_align: %u\n", block_align);
        #endif

        //read in format type (4 bytes)
        fread(&sample_size, 2, 1, file);

        #ifdef DEBUG
            fprintf(stdout, "sample_size: %u\n", sample_size);
        #endif

        wav->format_size = format_size;
        wav->format_type = format_type;
        wav->num_channels = num_channels;
        wav->sample_rate = sample_rate;
        wav->byte_rate = byte_rate;
        wav->block_align = block_align;
        wav->sample_size = sample_size;

        return 1;

    } else {

        return 0;

    }

    

}


uint8_t read_data_chunk(FILE* file, WAV* wav) {

    uint32_t data_size;
    uint32_t data_index;

    #ifdef DEBUG
    fprintf(stdout, "Attempting to read data chunk:\n");
    #endif

    uint32_t index;
    uint8_t found_chunk = find_chunk_header(file, "data", &index);

    //first data byte index is index of "data" header + 8 bytes (4 for header, 4 for data_size)
    data_index = index + 8;

    if (found_chunk) {
        //read in data size (4 bytes)
        fseek(file, index + 4, SEEK_SET);
        fread(&data_size, 4, 1, file);

        #ifdef DEBUG
            fprintf(stdout, "data_size: %u\n", data_size);
            fprintf(stdout, "data_index: %u\n", index + 8);
        #endif


        wav->data_size = data_size;
        wav->data_index = data_index; 

        return 1;

    } else {

        return 0;

    }


}


uint8_t find_chunk_header(FILE* file, char header[5], uint32_t* index) {


    char buffer[5] = "";
    uint32_t header_index = 0;

    rewind(file);

    //loop through file until chunk header is found
    int match = -1;
    while (match != 0) {
        fread(buffer, 4, 1, file);

        #ifdef DEBUG
            fprintf(stdout, "read: %s at index %u\n", buffer, (unsigned int) header_index);
        #endif

        match = strcmp((char*) buffer, (char*) header);
        if (match != 0) {
            header_index++;
            fseek(file, -3, SEEK_CUR);
        }
    }

    rewind(file);

    if (match == 0) {

        #ifdef DEBUG
            fprintf(stdout, "Found chunk header %s at index %u\n", header, (unsigned int) header_index);
        #endif


        *index = header_index;
        return 1;
    } else {

        fprintf(stderr, "Could not find chunk header.\n");

        return 0;
    }

}

WAV read_header(FILE* file) {

    WAV wav; 


    uint8_t valid_riff = read_riff_chunk(file, &wav);

    uint8_t valid_fmt = read_fmt_chunk(file, &wav);

    uint8_t valid_data = read_data_chunk(file, &wav);
    
    if (valid_riff && valid_fmt && valid_data) {
        wav.is_valid_wav = 1;
    } else {
        wav.is_valid_wav = 0;
    }


    return wav;

}