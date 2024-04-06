all: compile link run

compile:
	g++ -Isrc/include -c main.cpp Input.cpp

link:
	g++ main.o -o main Input.o -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

run:
	main.exe