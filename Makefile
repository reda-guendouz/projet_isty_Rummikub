CC=gcc
CFLAGS=-O2 -Wall `sdl2-config --cflags`
LIBS=`sdl2-config --libs` -lSDL2 -lSDL2_image -lSDL2_ttf
EXE=rummikub

all: graphics2.o modele.o controleur.c
	rm -f $(EXE)
	$(CC) $(CFLAGS) graphics2.o modele.o controleur.c -o $(EXE) $(LIBS)

graphics2.o: Vue/graphics2.c Vue/graphics2.h
	$(CC) $(CFLAGS) -c Vue/graphics2.c

modele.o: Modele/modele.c Modele/modele.h
	$(CC) $(CFLAGS) -c Modele/modele.c

clean:
	rm -f *.o
	rm -f $(EXE)
