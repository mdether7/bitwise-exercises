PROGRAM= bitwise
CC= cc
STD= -std=c99
CFLAGS= -c -g -Wall -Werror
LFLAGS= -lncurses -lpanel
OBJS= main.o binary.o display.o

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(OBJS) -o $(PROGRAM) $(LFLAGS)

%.o: %.c
	$(CC) $(STD) $(CFLAGS) -o $@ $<

main.o: main.c binarotator.h
binary.o: binary.c binarotator.h
display.o: display.c binarotator.h

clean: # make clean after running and debugging for example
	rm -f $(OBJS) $(PROGRAM)

.PHONY: all clean