CC=gcc
CFLAGS=-O2 -Wall `sdl-config --cflags`
LIBS=`sdl-config --libs` -lm -lSDL_ttf

%: graphics.o %.c

	rm -f $@
	$(CC) $(CFLAGS) graphics.o  $@.c -o $@ $(LIBS)

main: graphics.o main.c

		rm -f $@
		$(CC) $(CFLAGS) graphics.o  main.c -o main $(LIBS)



graphics.o: graphics.c graphics.h
	rm -f police.h
	touch police.h
	if test -e /usr/include/SDL_ttf.h;           then echo "#define SDL_TTF_OK" > police.h; fi
	if test -e /usr/include/SDL/SDL_ttf.h;       then echo "#define SDL_TTF_OK" > police.h; fi
	if test -e /usr/local/include/SDL_ttf.h;     then echo "#define SDL_TTF_OK" > police.h; fi
	if test -e /usr/local/include/SDL/SDL_ttf.h; then echo "#define SDL_TTF_OK" > police.h; fi
	$(CC) $(CFLAGS) -c graphics.c
Vue.o : Vue.c Vue.h
	$(CC) $(CFLAGS) -c Vue.c
Model.o : Model.c Model.h
	$(CC) $(CFLAGS) -c Model.c
Outils.o : Outils.c Outils.h
	$(CC) $(CFLAGS) -c Outils.c


clean:
	rm -f *core
	rm -f *.o
	rm -f main
	rm -f *.tar
