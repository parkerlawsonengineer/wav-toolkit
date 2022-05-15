#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include "stdio.h"
#include "wav_struct.h"




//=========General Purpose Functions=============

//attempt to open file, print to stderr and return NULL if file cannot be opened
FILE* open_file(char* filepath);





//=========Header Functions======================


/*  finds and reads the first section of the header file, the "RIFF" chunk. 
*   returns 1 if chunk was read successfully 
*   returns 0 if an error occurred while reading chunk.
*/
uint8_t read_riff_chunk(FILE* file, WAV* wav);

/*  finds and reads the format chunk of the header, which begins with the marker "fmt " 
*   returns 1 if chunk was read successfully 
*   returns 0 if an error occurred while reading chunk.
*/
uint8_t read_fmt_chunk(FILE* file, WAV* wav);

/*  finds and reads the data chunk of the header, which begins with the marker "data" 
*   returns 1 if chunk was read successfully 
*   returns 0 if an error occurred while reading chunk.
*/
uint8_t read_data_chunk(FILE* file, WAV* wav);

/* finds a header, given a pointer to a file and the expected header string
*  places the index of the first byte in the chunk marker in index variable passed by pointer to the function
*  returns 0 if header was not found
*  returns 1 if header was found
*  rewinds file pointer to beginning of file
*/
uint8_t find_chunk_header(FILE* file, char header[5], uint32_t* index);

/* read header information into WAV struct, then return struct.
*  sets is_valid_wav value to 1 if reads are successful
*  sets is_valid_wav value to 0 if reads are unsuccessful
*/
WAV read_header(FILE* file);


#endif