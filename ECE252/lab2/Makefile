CC=gcc
CFLAGS=-Wall -g
LD=gcc
LDFLAGS=-g



default: all

all: bin paster

bin: 
	mkdir -p bin/



paster:
	gcc -g paster.c crc.c helper.c zutil.c -lz -lcurl -pthread -o bin/paster


clean:
	rm -rf bin/ 
	rm all.png