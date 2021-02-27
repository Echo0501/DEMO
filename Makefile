
CC = gcc
CFLAGS = -Wall -O3 -pg


all: main

main: main.o vec.o geom.o cube.o NoobSDL.o OpenSimplexNoise.o
	$(CC) $(CFLAGS) -o $@ $^ -lm -lpthread `sdl2-config --cflags --libs`

OpenSimplexNoise.o: OpenSimplexNoise.cpp OpenSimplexNoise.h
	$(CC) $(CFLAGS) -c $< -lm

NoobSDL.o: NoobSDL.c NoobSDL.h
	$(CC) $(CFLAGS) -c $< `sdl2-config --cflags --libs`

cube.o: cube.c vec.h geom.h cube.h
	$(CC) $(CFLAGS) -c $<

geom.o: geom.cpp vec.h geom.h cube.h
	$(CC) $(CFLAGS) -c $< -lm

vec.o: vec.c vec.h
	$(CC) $(CFLAGS) -c $< -lm

main.o: main.cpp vec.h geom.h cube.h NoobSDL.h OpenSimplexNoise.h
	$(CC) $(CFLAGS) -c $< -lm -lpthread `sdl2-config --cflags --libs`

clean:
	rm -f *.o
	rm -f main