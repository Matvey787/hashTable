# Compiler and flags
CXX = g++
SANITIZER = 
CXXFLAGS = -I inc -g -mavx -D _DEBUG -std=c++17 -O2 -Wall -Wextra -Weffc++

# Object files
OBJECTS = obj/main.o obj/hash_utils.o obj/handText.o

# Default target
all: init out

# Link
out: $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(CXXFLAGS) $(SANITIZER)

# Compile source files
obj/%.o: src/%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(SANITIZER)

# Clean
clean:
	rm -rf out obj/*.o 

init:
	mkdir -p obj