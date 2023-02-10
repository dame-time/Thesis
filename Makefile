# author: Davide Paolillo
# Thesis - a.a. 2022/2023

# name of the file
FILENAME = Main

# Visual Studio compiler
CC = clang++

# Include path
IDIR = -I./Includes -I./Includes/libigl

# compiler flags:
CCFLAGS  = -g -O3 -x c++ -mmacosx-version-min=11.1 -Wall -Wno-invalid-offsetof -std=c++11

# linker flags:
LFLAGS = 

SOURCES = ./Includes/glad/glad.c $(shell python ./getCPPFilePaths.py)
PARTIAL_SOURCES = $(shell python ./findAllObjs.py $(ARGS))

OBJECTS = $(SOURCES:.c=.o)
PARTIAL_OBJECTS = $(PARTIAL_SOURCES:.c=.o)

TARGET = ./Build/Thesis.out

.PHONY : all
all: $(OBJECTS)
	$(CC) $(OBJECTS) $(LFLAGS) -o $(TARGET)

.PHONY : partial
partial: $(PARTIAL_OBJECTS)
	$(CC) $(PARTIAL_OBJECTS) $(LFLAGS) -o $(TARGET)

.c.o:
	$(CC) $(CCFLAGS) $(IDIR) -c $< -o $@

.PHONY : clean
clean :
	del *.o $(TARGET)