CC = g++ -std=c++11
CGFLAGS = -Wall -Wfatal-errors 

all: test_dijkstra.x

.PHONY: graph
graph:
	make -C ../../Graph_Src

test_dijkstra.x: test_dijkstra.o graph
	$(CC) $(CGFLAGS) -o $@ test_dijkstra.o ../../Graph_Src/*.o

%.o: %.cpp
	$(CC) $(CGFLAGS) -o $@ -c $< 

clean:
	rm -f *.o

realclean: clean
	rm -f *.x
	make -C ../../Graph_Src realclean
