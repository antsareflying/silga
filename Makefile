CC = gcc
LDFLAGS = -I$(CURDIR)/include -L$(CURDIR)/lib
LDLIBS = -l:libsodium.a
CFLAGS = -g -Wall -std=c11

silga.exe: silga.o
	$(CC) ./silga.o $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o silga.exe

silga.o: silga.c 

