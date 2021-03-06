all: main Makefile
	./main
main: Makefile src/*.cpp src/*.h
	g++ -Wl,-Map=main.map -std=c++11 -Os -fno-exceptions -fno-rtti -fomit-frame-pointer -o main -I./src src/*.cpp -lGL -lSDL2 -lGLEW
	# this will drop some k. keep it for cutting stage
	# this might also be a good starting point for custom libc: https://github.com/ensc/dietlibc
	#
	# this will lower size dramatically:
	# g++ -std=c++11 -Os  -fno-exceptions -fno-rtti -fomit-frame-pointer -o main -I./src src/*.cpp -lGL -lGLU -lSDL2 -lGLEW
	strip -s -R .comment -R .gnu.version main
	tools/ELFkickers/sstrip/sstrip main
	upx --best main
	#
	# sstrip can be obtained here: https://github.com/BR903/ELFkickers/tree/master/sstrip
	
