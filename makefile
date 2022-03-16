all: compile link clean run

compile:
	g++ -Iinclude -Iheader -c src/main.cpp src/enemies.cpp src/game.cpp

link:
	g++ main.o enemies.o game.o -o IoR -Llib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean:
	del -f *.o

run:
	./IoR