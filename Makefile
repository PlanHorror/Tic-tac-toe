all:
	g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2_ttf -lSDL2
clean:
	del main.exe