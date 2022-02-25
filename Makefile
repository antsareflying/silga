CC = gcc
LDFLAGS = -I$(CURDIR)/include -L$(CURDIR)/lib
LDLIBS = -lsodium
CFLAGS = -g -Wall -Wextra -std=c17
BIN = ./bin
SRC = ./src
OBJ = ./obj

all: $(BIN)/silga.exe

$(BIN)/silga.exe: $(OBJ)/silga.o
	$(CC) $(OBJ)/silga.o $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(BIN)/silga.exe

$(OBJ)/silga.o: $(SRC)/silga.c 
	$(CC) -c $(SRC)/silga.c  $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(OBJ)/silga.o

# rm -Recurse -Force c:/users/seong/programming/silga/bin/silga.exe
# rm -Recurse -Force c:/users/seong/programming/silga/obj/silga.o

naive: $(BIN)/naive.exe
$(BIN)/naive.exe: $(OBJ)/naive.o
	$(CC) $(OBJ)/naive.o $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(BIN)/naive.exe

$(OBJ)/naive.o: $(SRC)/naive.c 
	$(CC) -c $(SRC)/naive.c  $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(OBJ)/naive.o
clean: 
	
	@echo %PATH%


