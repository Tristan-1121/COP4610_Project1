# COP4610 Project 1
# Memory Management

# Author: Tristan Cameron


# Compiler
CC = g++
CFLAGS = -std=c++11 -Wall

# Files
TARGET = memory_manager
OBJ = main.o

# Build target
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -f $(OBJ) $(TARGET)
