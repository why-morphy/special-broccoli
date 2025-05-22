all:
	gcc -g -c main.cpp -Isrc/include -Lsrc/lib -lmingw32 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2 