CC = g++
FLAGS = -std=c++11
COMPILE_FLAGS = $(FLAGS) -c 

all:main

main:Main.o Game.o GameObject.o
	$(CC) Main.o  Game.o GameObject.o TileMap.o $(FLAGS) -o main -lsfml-graphics -lsfml-window -lsfml-system

main.o:Main.cpp Game.o
	$(CC) $(COMPILE_FLAGS)  Main.cpp

Game.o:Game.cpp TileMap.o GameObject.o 
	$(CC) $(COMPILE_FLAGS)  Game.cpp

TileMap.o:TileMap.cpp 
	$(CC) $(COMPILE_FLAGS)  TileMap.cpp
	
GameObject.o:GameObject.cpp 
	$(CC) $(COMPILE_FLAGS)  GameObject.cpp
	
clean:
	rm *.o main
