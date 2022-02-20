CC = g++

SRC = $(wildcard src/*.cpp) $(wildcard src/**/*.cpp) $(wildcard lib/**/**/*.c)

LIBS_STATIC = -static -lglfw3 -opengl32 -lgdi32 -static-libgcc -static-libstdc++ -lpthread
LIBS_DYN = -lglfw3.dll 

CFLAGS = -Wall -Wextra -g3 -Ilib -Ilib/glad/include -Isrc

OUT = bin/main

build:
	$(CC) $(SRC) $(CFLAGS) -O2 $(LIBS_STATIC) -o $(OUT)

debug:
	$(CC) $(SRC) $(CFLAGS) $(LIBS_DYN) -o $(OUT)
