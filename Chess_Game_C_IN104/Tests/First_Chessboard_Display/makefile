CC = gcc
CFLAGS = -Wall -Wfatal-errors
LDFLAGS = -Iinclude -lSDL2main -lSDL2

all: main_test_1.x Win_Screen_Load.x

main_test_1.x: Piece.o Image.o Audio.o main_test_1.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

Win_Screen_Load.x: Image.o Win_Screen_Load.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o

realclean: clean
	rm -f *.x