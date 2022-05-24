#ifndef PRINT_H
#define PRINT_H

#include "wav_struct.h"


/*  prints the full header information of the file (only supported header chunks)
*/
void print_header(WAV wav);

/* prints the riff chunk of the header, if provided a valid header file
*/
void print_header_riff(WAV wav);

/* prints the fmt chunk of the header, if provided a valid header file
*/
void print_header_fmt(WAV wav);

/* prints the data chunk of the header, if provided a valid header file
*/
void print_header_data(WAV wav);



#endif