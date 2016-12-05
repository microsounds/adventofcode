CC=gcc
CFLAGS=-ansi -O2
DEBUG=-g -Wall -Wextra
LDFLAGS=-lm -lcrypto
SRC=code
INPUT=$(wildcard $(SRC)/*.c)
OUTPUT=$(patsubst $(SRC)/%.c,%, $(INPUT))

all: $(OUTPUT)

$(OUTPUT): $(INPUT) # rebuild on all changes
	$(CC) $(CFLAGS) $(DEBUG) -o $@ $(patsubst %,$(SRC)/%.c, $@) $(LDFLAGS)
	

clean:
	rm -rf $(OUTPUT)
