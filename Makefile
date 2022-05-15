

CFLAGS = -DDEBUG



default: wav_toolkit

wav_toolkit: build/wav_toolkit.o build/file_utils.o
	gcc $(CFLAGS) -o wav_toolkit build/wav_toolkit.o build/file_utils.o

build/wav_toolkit.o: wav_toolkit.c wav_struct.h
	gcc $(CFLAGS) -c wav_toolkit.c -o build/wav_toolkit.o

build/file_utils.o: file_utils.c file_utils.h wav_struct.h
	gcc $(CFLAGS) -c file_utils.c -o build/file_utils.o
