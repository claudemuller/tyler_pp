UNAME_S := $(shell uname -s)
CC=g++
CFLAGS=-Wall -Wfatal-errors -std=c++17
INCS=-I./libs/ -I./libs/lua/
LIBS=
LFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua
SRC=./src/*.cpp \
	./src/Engine/*.cpp \
	./src/Logger/*.cpp
BIN=gameengine

# Mac Stuff
ifeq ($(UNAME_S),Darwin)
	INCS+= -I/opt/homebrew/include -I/opt/homebrew/Cellar/sdl2/2.26.3/include/SDL2/
	LIBS+= -L/opt/homebrew/lib -L/opt/homebrew/lib/
endif

all: clean build run

build:
	$(CC) $(SRC) $(CFLAGS) $(INCS) $(LIBS) $(LFLAGS) -o $(BIN)

debug:
	$(CC) -g $(SRC) $(CFLAGS) $(INCS) $(LIBS) $(LFLAGS) -o debug

run:
	./$(BIN)

clean:
	rm -rf $(BIN) debug*
