CC = gcc
CFLAGS = -Wall -Wfatal-errors
LDFLAGS = -Iinclude -lSDL2main -lSDL2

all: Chess_Game.x

Chess_Game.x: Chess_Game.o Board.o Graphics.o Mouse.o Move_Log.o Move.o Piece.o Player.o Timer.o Conversion.o Image.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o

realclean: clean
	rm -f *.x