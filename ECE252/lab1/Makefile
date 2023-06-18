CC=gcc
CFLAGS=-Wall -g
LD=gcc
LDFLAGS=-g



default: all

all: bin findpng catpng

bin: 
	mkdir -p bin/



findpng:
	gcc -g findpng.c ./starter/png_util/pnginfo.c ./starter/png_util/crc.c ./starter/png_util/zutil.c -lm -lz -o bin/findpng

catpng:
	gcc -g catpng.c ./starter/png_util/pnginfo.c ./starter/png_util/crc.c ./starter/png_util/zutil.c -lm -lz -o bin/catpng

clean:
	rm -rf bin/ 

