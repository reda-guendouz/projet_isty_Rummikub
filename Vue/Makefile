CC=gcc
CFLAGS=-O2 -Wall `sdl2-config --cflags`
LIBS=`sdl2-config --libs` -lSDL2 -lSDL2_image -lSDL2_ttf
EXE=rummikub

all: graphics2.o main.c
	rm -f $(EXE)
	$(CC) $(CFLAGS) graphics2.o  main.c -o $(EXE) $(LIBS)

graphics2.o: graphics2.c graphics2.h
	$(CC) $(CFLAGS) -c graphics2.c $(LIBS)

clean:
	rm -f *core
	rm -f *.o
	rm -f $(EXE)
	rm -f *.tar
