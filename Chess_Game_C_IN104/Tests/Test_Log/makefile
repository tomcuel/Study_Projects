CC = gcc
CFLAGS = -Wall -Wfatal-errors
LDFLAGS = -Iinclude -lSDL2main -lSDL2

all: test_log.x test_move.x

test_move.x: Move.o test_move.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test_log.x: Move.o Move_Log.o test_log.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o

realclean: clean
	rm -f *.x