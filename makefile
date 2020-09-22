all: build_util build_entities build_breakout build_main link
linux: build_util build_entities build_breakout build_main link_alt

.PHONY: all

run: 
	./main.out

link:
	g++ -o main.out *.o -L"freeglut\lib" -lfreeglut -lopengl32

link_alt:
	g++ -o main.out *.o -L"freeglut\lib" -lglut -lGL

build_main:
	g++ -c main.cpp -I"freeglut\include" 

build_breakout:
	g++ -c breakout/*.cpp -I"freeglut\include" 

build_entities:
	g++ -c entities/*.cpp -I"freeglut\include" 

build_util:
	g++ -c util/*.cpp -I"freeglut\include" 

clean:
	rm -f *.o *.exe
