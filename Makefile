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

$(OBJ)silga.o: $(SRC)silga.c 

clean:
	Remove-item $(BIN)/*.exe $(OBJ)/*.o

