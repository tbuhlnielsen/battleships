# C++ compiler
CXX = clang++
CXXFLAGS = -std=c++14

# source code: all files with .cpp extension
SRC = $(wildcard *.cpp)

# object files: take source file stems and replace extension with .o
OBJ = $(SRC:%.cpp=%.o)

# name of executable program
TARGET = main

# there aren't actually any targets called `all` or `clean`
.PHONY: all clean

# first rule is carried out by default
all: $(TARGET)

# link all object files to form executable
$(TARGET): $(OBJ)
	$(CXX) $^ -o $@

# given a single source file, compile to an object file (built-in)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# add dependencies here, e.g. main.o: header.h
ai.o: utils.h
game.o: game.h players.h
main.o: game.h
pieces.o: constants.h pieces.h
players.o: ai.h players.h
utils.o: pieces.h utils.h

# remove "auxilliary" files	
clean:
	rm $(TARGET) $(OBJ)