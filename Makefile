CC = clang
CFLAGS = -Wall -Wextra -Wpedantic -std=c23 -lraylib -o $(BIN)
SRC = src/main.c
BIN = cats

.PHONY: all build clean
all: build

build:
	$(CC) $(CFLAGS) $(SRC)

clean:
	rm $(BIN)
