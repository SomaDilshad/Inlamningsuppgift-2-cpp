# Makefile for IoT Measurement Analyzer
# Compiler settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I.

# Executable name
TARGET = iot_analyzer

# Source files
SRCS = main.cpp measurement.cpp data_manager.cpp

# Object files (generated from source files)
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run
