CC = gcc
CFLAGS = -Wall -Wfatal-errors
LDFLAGS = -Iinclude -lSDL2main -lSDL2

all : Audio.o 

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o

realclean: clean
	rm -f *.x