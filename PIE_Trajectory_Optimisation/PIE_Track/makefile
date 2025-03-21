CC = g++ -std=c++17
CGFLAGS = -Wall -Wfatal-errors 

all: track_modelling.x

.PHONY: graph
graph:
	make -C ../Graph_Src

track_modelling.x: track_modelling.o graph
	$(CC) $(CGFLAGS) -o $@ track_modelling.o ../Graph_Src/*.o

%.o: %.cpp
	$(CC) $(CGFLAGS) -o $@ -c $< 

clean:
	rm -f *.o

realclean: clean
	rm -f *.x
	make -C ../Graph_Src clean
