CC = g++ -std=c++11
CGFLAGS = -Wall -Wfatal-errors

all: first_track_examples.x second_track_examples.x multi_point_track_examples.x launcher.x

.PHONY: graph
graph:
	make -C ../Graph_Src

launcher.x: launcher.o graph
	$(CC) $(CGFLAGS) -o $@ launcher.o ../Graph_Src/*.o

first_track_examples.x: first_track_examples.o graph
	$(CC) $(CGFLAGS) -o $@ first_track_examples.o ../Graph_Src/*.o

second_track_examples.x: second_track_examples.o graph
	$(CC) $(CGFLAGS) -o $@ second_track_examples.o ../Graph_Src/*.o

multi_point_track_examples.x: multi_point_track_examples.o graph
	$(CC) $(CGFLAGS) -o $@ multi_point_track_examples.o ../Graph_Src/*.o

%.o: %.cpp
	$(CC) $(CGFLAGS) -o $@ -c $< 

clean:
	rm -f *.o

realclean: clean
	rm -f *.x
	make -C ../Graph_Src realclean
