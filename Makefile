CXX = clang++
CXXFLAGS = -std=c++17

# -- Project files --
SRC = $(wildcard src/*.cpp)

# -- Executable program --
TARGET = main

.PHONY: all clean

all: $(TARGET)

# -- Link --
OBJ = $(SRC:src/%.cpp=build/%.o)

$(TARGET): $(OBJ)
	$(CXX) $^ -o $@

# -- Compile --
DEPS = $(OBJ:build/%.o=build/%.d)
-include $(DEPS)

## Compile a source file, put resulting dependency and object files
## in build directory (with same structure as source directory).
build/%.o: src/%.cpp 
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

# -- Remove auxiliary files --
clean:
	rm $(TARGET)
	rm -r build