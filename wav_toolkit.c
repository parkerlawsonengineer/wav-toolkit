//project-specific includes
#include "file_utils.h"
#include "wav_struct.h"
#include "print.h"

//std includes
#include "stdlib.h"




int main(int argc, char* argv[]) {

    //TODO: add support for command-line arguments


    FILE* input_wav_file = open_file("test.wav");    

    if (input_wav_file == NULL) {
        return 1;
    }

    WAV input_wav = read_header(input_wav_file);
    

    print_header(input_wav);

    


    fclose(input_wav_file);

}