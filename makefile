all: build_entities build_breakout build_main link
.PHONY: all

run: 
	./main

link:
	g++ -o main *.o -L"glew\lib" -L"freeglut\lib" -lglew32 -lfreeglut -lopengl32

build_main:
	g++ -c main.cpp -I"freeglut\include" -I"glew\include"

build_breakout:
	g++ -c breakout/*.cpp -I"freeglut\include" -I"glew\include"

build_entities:
	g++ -c entities/*.cpp -I"freeglut\include" -I"glew\include"

clean:
	rm -f *.o *.exe
