all:
	g++ -Isrc/include -L src/lib -o main main.cpp -lmingw64 -lSDL2main -lSDL2