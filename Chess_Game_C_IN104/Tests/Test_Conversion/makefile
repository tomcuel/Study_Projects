CC = gcc
CFLAGS = -Wall -Wfatal-errors

all: test_Conversion.x

test_Conversion.x: test_Conversion.o Conversion.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o

realclean: clean
	rm -f *.x