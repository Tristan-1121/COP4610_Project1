# COP4610 Project 1
# Memory Management

# Author: Tristan Cameron


# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Target executable name
TARGET = memory_manager

# Source files
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

# Build target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Default target to build and run the program
all: $(TARGET)
	./$(TARGET)
