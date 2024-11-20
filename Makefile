# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -g

# Files
SRC = celda.cpp juego.cpp main.cpp movimiento.cpp tablero.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = main

# Default target
all: $(EXEC)

# Build the executable
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJ)

# Compile source files into object files
%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean generated files
clean:
	rm -f $(OBJ) $(EXEC)
