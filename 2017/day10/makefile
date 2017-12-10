CC=gcc
CFLAGS=-O2 -ansi
DEBUG=-g -Wall
LDFLAGS=-lm
OUTPUT=$(notdir $(CURDIR))
INPUT=$(wildcard *.c)

all:
	$(CC) $(CFLAGS) $(DEBUG) -o $(OUTPUT) $(INPUT) $(LDFLAGS)
clean:
	rm -rf $(OUTPUT)
