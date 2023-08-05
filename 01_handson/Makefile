CC = /usr/bin/gcc
LINK = /usr/bin/gcc

CFLAGS = -Wall -ggdb3 -O0 -no-pie

BIN = chall
SRC := $(wildcard *.c)

all: $(BIN)

$(BIN):
	$(CC) $(CFLAGS) -o $(BIN) $(SRC)

clean:
	rm $(BIN)