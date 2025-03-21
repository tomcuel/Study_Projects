CC=g++ -std=c++11
CGFLAGS=-Wall -Wfatal-errors 

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

all: $(OBJ)

%.o: %.cpp
	$(CC) $(CGFLAGS) -o $@ -c $<

clean:
	rm -f *.o

realclean: clean
	rm -f *.x