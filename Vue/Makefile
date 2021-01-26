CC=gcc
CFLAGS=-O2 -Wall `sdl2-config --cflags`
LIBS=`sdl2-config --libs` -lm -lSDL_ttf

all: graphics.o main.c
	rm -f main
	$(CC) $(CFLAGS) graphics.o  main.c -o main $(LIBS)

graphics.o: graphics2.c graphics2.h
	$(CC) $(CFLAGS) -c graphics2.c

clean:
	rm -f *core
	rm -f *.o
	rm -f main
	rm -f *.tar
