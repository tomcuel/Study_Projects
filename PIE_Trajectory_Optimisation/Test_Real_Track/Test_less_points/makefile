CC = g++ -std=c++11
CGFLAGS = -Wall -Wfatal-errors 

all: track_modelling_test__less_points.x

.PHONY: graph
graph:
	make -C ../../Graph_Src

track_modelling_test__less_points.x: track_modelling_test__less_points.o graph
	$(CC) $(CGFLAGS) -o $@ track_modelling_test__less_points.o ../../Graph_Src/*.o

%.o: %.cpp
	$(CC) $(CGFLAGS) -o $@ -c $< 

clean:
	rm -f *.o

realclean: clean
	rm -f *.x
	make -C ../../Graph_Src clean
