CC = gcc
FLAGS= -Wall -g

all: graph

graph: main.o libgraph.a
	$(CC) $(FLAGS) -o graph main.o libgraph.a

main.o: main.c graph.h
	$(CC) $(FLAGS) -c main.c

libgraph.a: graph.o algo.o
	ar -rcs -o libgraph.a graph.o algo.o

graph.o: graph.c graph.h
	$(CC) $(FLAGS) -c graph.c

algo.o: algo.c graph.h
	$(CC) $(FLAGS) -c algo.c

clean:
	rm -f *.o *.a graph