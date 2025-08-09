PROGRAM= bitwise
CC= cc
CFLAGS= -c -g -Wall
OBJS= main.o binary.o display.o

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(OBJS) -o $(PROGRAM)

%.o: %.c
	$(CC) $(CFLAGS) $<

main.o: main.c display.h binary.h 
binary.o: binary.c binary.h
display.o: display.c display.h

clean: # make clean after running and debugging for example
	rm -f $(OBJS) $(PROGRAM)

.PHONY: all clean