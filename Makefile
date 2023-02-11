# author: Davide Paolillo
# Thesis - a.a. 2022/2023

# name of the file
FILENAME = Main

# Visual Studio compiler
CC = clang++

# Include path
IDIR = -I/usr/local/include/eigen3 -I./Includes -I./Includes/libigl -I./Includes/imgui -I./Includes/imguizmo -I./System

# compiler flags:
CCFLAGS  = -g -O3 -mmacosx-version-min=11.1 -Wall -Wno-invalid-offsetof -std=c++11

# linker flags:
LFLAGS = -lpthread -L./Includes/Libraries -lglfw3 -lassimp -lassimpd -lz -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

SOURCES = ./Includes/src/glad.c $(shell python ./getCPPFilePaths.py)
COMPILED_SOURCES = $(shell python ./findAllObjs.py)
PARTIAL_SOURCES = $(shell python ./findNotCompiledObjs.py $(ARGS))

TARGET = ./Build/Thesis.out

.PHONY : all
all:
	$(CC) $(CCFLAGS) -c $(IDIR) $(SOURCES) $(LFLAGS)

.PHONY : run
run:
	$(CC) $(CCFLAGS) $(IDIR) $(COMPILED_SOURCES) -o $(TARGET) $(LFLAGS)

.PHONY : partial
partial:
	$(CC) $(CCFLAGS) -c $(IDIR) $(PARTIAL_SOURCES) $(LFLAGS)

.PHONY : clean
clean :
	rm -f ./.objs/*.o $(TARGET)