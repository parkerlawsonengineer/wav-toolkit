

CFLAGS = -DDEBUG



default: wav_toolkit

wav_toolkit: build/wav_toolkit.o build/file_utils.o build/print.o
	gcc $(CFLAGS) -o wav_toolkit \
		build/wav_toolkit.o \
		build/file_utils.o \
		build/print.o

build:
	mkdir build

build/wav_toolkit.o: wav_toolkit.c wav_struct.h | build
	gcc $(CFLAGS) -c wav_toolkit.c -o build/wav_toolkit.o

build/file_utils.o: file_utils.c file_utils.h wav_struct.h | build
	gcc $(CFLAGS) -c file_utils.c -o build/file_utils.o

build/print.o: print.c print.h wav_struct.h | build
	gcc $(CFLAGS) -c print.c -o build/print.o
