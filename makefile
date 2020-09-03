all: build run
.PHONY: all

run:
	./main

build: build_main link

link:
	g++ -o main *.o -L"glew\lib" -L"freeglut\lib" -lglew32 -lfreeglut -lopengl32

build_main:
	g++ -c main.cpp -I"freeglut\include" -I"glew\include"

clean:
	rm -f *.o *.exe
