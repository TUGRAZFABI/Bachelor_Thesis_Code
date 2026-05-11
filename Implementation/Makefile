# Simple Makefile for Windows with MinGW

# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Iinclude -Ieigen-3.4.0

# Directories
SRC_DIR = src
INCLUDE_DIR = include/anomaly_detect
OUTPUT_DIR = output

# Target name
TARGET = anomaly_detection

# Find all source files in src directory
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
# Add main file
SOURCES += anomaly_detection.cpp

# Generate object file names
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Build the program by linking all object files
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET).exe $(OBJECTS)
	@echo "Build complete: $(TARGET).exe"

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Alternative: single command to compile everything
quick: 
	$(CXX) $(CXXFLAGS) -o $(TARGET).exe $(SOURCES)

# Run the program
run: $(TARGET)
	./$(TARGET).exe

# Clean the executable and object files
clean:
	del $(TARGET).exe $(SRC_DIR)\*.o *.o 2>nul || true

# Clean everything including object files
cleanall: clean
	@echo "Cleaned all build files"

# Help command
help:
	@echo "Commands (use mingw32-make):"
	@echo "  mingw32-make       - Build the program (compiles all .cpp files)"
	@echo "  mingw32-make quick - Quick build (single command)"
	@echo "  mingw32-make run   - Build and run"
	@echo "  mingw32-make clean - Remove executable and object files"
	@echo "  mingw32-make cleanall - Clean everything"

# Debug build
debug: CXXFLAGS += -g -DDEBUG
debug: clean $(TARGET)
	@echo "Debug build complete"

.PHONY: all run clean cleanall help debug quick