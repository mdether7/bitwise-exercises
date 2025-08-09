PROGRAM= bitwise
CC= cc
CFLAGS= -c -g -Wall
LFLAGS= -lncurses -lpanel
OBJS= main.o binary.o display.o

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(OBJS) -o $(PROGRAM) $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

main.o: main.c display.h binary.h 
binary.o: binary.c binary.h
display.o: display.c display.h

clean: # make clean after running and debugging for example
	rm -f $(OBJS) $(PROGRAM)

.PHONY: all clean