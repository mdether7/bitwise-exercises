PROGRAM= bitwise
CC= cc
CFLAGS= -c -g -Wall
OBJS= main.o binary.o

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(OBJS) -o $(PROGRAM)

%.o: %.c
	$(CC) $(CFLAGS) $<

main.o: main.c binary.h

binary.o: binary.c binary.h

clean: # make clean after running and debugging for example
	rm -f $(OBJS) $(PROGRAM)

.PHONY: all clean