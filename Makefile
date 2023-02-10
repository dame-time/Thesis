# author: Davide Paolillo
# Thesis - a.a. 2022/2023

# name of the file
FILENAME = Main

# Visual Studio compiler
CC = clang++

# Include path
IDIR = -I./Includes -I./Includes/libigl

# compiler flags:
CCFLAGS  = -g -O3 -mmacosx-version-min=11.1 -Wall -Wno-invalid-offsetof -std=c++11

# linker flags:
LFLAGS = -L./Includes/Libraries -lglfw3 -lassimp -lassimpd -lz -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

SOURCES = ./Includes/src/glad.c $(shell python ./getCPPFilePaths.py)
PARTIAL_SOURCES = $(shell python ./findAllObjs.py $(ARGS))

OBJECTS = $(SOURCES:.c=.o)
PARTIAL_OBJECTS = $(PARTIAL_SOURCES:.c=.o)

TARGET = ./Build/Thesis.out

.PHONY : all
all: $(OBJECTS)
	$(CC) $(CCFLAGS) $(IDIR) $(OBJECTS) -o $(TARGET) $(LFLAGS)

.PHONY : partial
partial: $(PARTIAL_OBJECTS)
	$(CC) $(CCFLAGS) $(IDIR) $(PARTIAL_OBJECTS) -o $(TARGET) $(LFLAGS)

.c.o:
	$(CC) $(CCFLAGS) -c $< -o $@

.PHONY : clean
clean :
	rm -f ./.objs/*.o $(TARGET)