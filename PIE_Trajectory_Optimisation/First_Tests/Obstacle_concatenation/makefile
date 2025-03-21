CC = g++ -std=c++11
CGFLAGS = -Wall -Wfatal-errors 

all: test_obstacle_concatenation.x

.PHONY: graph
graph:
	make -C ../../Graph_Src

test_obstacle_concatenation.x: test_obstacle_concatenation.o graph
	$(CC) $(CGFLAGS) -o $@ test_obstacle_concatenation.o ../../Graph_Src/*.o

%.o: %.cpp
	$(CC) $(CGFLAGS) -o $@ -c $< 

clean:
	rm -f *.o

realclean: clean
	rm -f *.x
	make -C ../../Graph_Src realclean
