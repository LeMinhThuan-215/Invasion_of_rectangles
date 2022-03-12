all: compile link run

compile:
	g++ -Isrc/include -c main.cpp enemies.cpp game.cpp

link:
	g++ main.o enemies.o game.o -o IoR -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

run:
	./IoR