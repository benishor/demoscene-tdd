all: main Makefile
	./main
main: Makefile src/*.cpp
	g++ -std=c++11 -Os -o main -I./src src/*.cpp -lGL -lGLU -lSDL2
	
