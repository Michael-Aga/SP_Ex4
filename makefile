CC = gcc
AR = ar
FLAGS= -Wall -g

all: complete_graph

complete_graph: main.o graph_libs.so
	$(CC) $(FLAGS) -o complete_graph main.o graph_libs.so

main.o: main.c graph.h
	$(CC) $(FLAGS) -c main.c

graph_libs.so: graph.o algo.o
	$(AR) -rcs graph_libs.so graph.o algo.o

graph.o: graph.c graph.h
	$(CC) $(FLAGS) -c graph.c

algo.o: algo.c graph.h
	$(CC) $(FLAGS) -c algo.c

clean:
	rm -f *.o *.so complete_graph