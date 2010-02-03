#Compiler
CC=g++

#Compiler Flags
CFLAGS=-c -Wall -Wextra

all: c0mbat

c0mbat: main.o gameEngine.o gameMap.o gameObject.o gameObjectHandler.o player.o
	$(CC) main.o gameEngine.o gameMap.o gameObject.o gameObjectHandler.o player.o -o c0mbat -lSDL

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

gameEngine.o: gameEngine.cpp 
	$(CC) $(CFLAGS) gameEngine.cpp 

gameMap.o: gameMap.cpp
	$(CC) $(CFLAGS) gameMap.cpp 

gameObject.o: gameObject.cpp
	$(CC) $(CFLAGS) gameObject.cpp 

gameObjectHandler.o: gameObjectHandler.cpp
	$(CC) $(CFLAGS) gameObjectHandler.cpp 

player.o: player.cpp
	$(CC) $(CFLAGS) player.cpp

clean: 
	rm -rf *o abc
