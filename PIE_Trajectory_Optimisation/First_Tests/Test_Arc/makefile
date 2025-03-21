CC = g++ -std=c++11
CGFLAGS = -Wall -Wfatal-errors 

all: test_arc.x

.PHONY: graph
graph:
	make -C ../../Graph_Src

test_arc.x: test_arc.o graph
	$(CC) $(CGFLAGS) -o $@ test_arc.o ../../Graph_Src/*.o

%.o: %.cpp
	$(CC) $(CGFLAGS) -o $@ -c $< 

clean:
	rm -f *.o

realclean: clean
	rm -f *.x
	make -C ../../Graph_Src realclean
