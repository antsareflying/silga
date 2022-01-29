CC = gcc
LDFLAGS = -I$(CURDIR)/include -L$(CURDIR)/lib
LDLIBS = -lsodium
CFLAGS = -g -Wall -Wextra -std=c11
BIN = ./bin
SRC = ./src
OBJ = ./obj

all: $(BIN)/silga.exe

$(BIN)/silga.exe: $(OBJ)/silga.o
	$(CC) $(OBJ)/silga.o $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(BIN)/silga.exe

$(OBJ)/silga.o: $(SRC)/silga.c 
	$(CC) -c $(SRC)/silga.c  $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(OBJ)/silga.o

clean: 
	rm -Recurse -Force bin/silga.exe
	rm -Recurse -Force obj/silga.o


