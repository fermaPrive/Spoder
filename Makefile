CC = gcc
CFLAGS = -Wall -g -std=c99 -pedantic

OBJECTS = main.o utilities.o

.PHONY: all clean

all: main


main: $(OBJECTS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c -o $@ $<

main.o: main.c utilities.h
utilities.o: utilities.c  utilities.h


clean:
	rm -rf *.o main