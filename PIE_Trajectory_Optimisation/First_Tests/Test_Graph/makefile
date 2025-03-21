CC = g++ -std=c++11
CGFLAGS = -Wall -Wfatal-errors 

all: test_graph.x

.PHONY: graph
graph:
	make -C ../../Graph_Src

test_graph.x: test_graph.o graph
	$(CC) $(CGFLAGS) -o $@ test_graph.o ../../Graph_Src/*.o

%.o: %.cpp
	$(CC) $(CGFLAGS) -o $@ -c $< 

clean:
	rm -f *.o

realclean: clean
	rm -f *.x
	make -C ../../Graph_Src realclean
