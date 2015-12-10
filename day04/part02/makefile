CC=gcc
LANG=c
CFLAGS=-O2 -ansi
LDFLAGS=-lcrypto
PNAME=day04p02
OUTPUT=$(PNAME)
INPUT=$(PNAME).$(LANG)

all: $(INPUT)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(OUTPUT) $(INPUT)

clean:
	rm -rf $(OUTPUT)

