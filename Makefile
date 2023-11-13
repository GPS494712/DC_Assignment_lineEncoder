all:
	g++ -I/opt/homebrew/include -D_THREAD_SAFE -L/opt/homebrew/lib -lSDL2 -lSDL2main -lSDL2_ttf main.c++ -o main
