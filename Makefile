PROGRAM= bitwise
CC= cc
CFLAGS= -c -g -Wall
OBJS= main.o

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(OBJS) -o $(PROGRAM)

%.o: %.c
	$(CC) $(CFLAGS) $<

clean: # make clean after running and debugging for example
	rm -f $(OBJS) $(PROGRAM)

.PHONY: all clean