# Compiler and flags
CXX = gcc
SANITIZER = 
CXXFLAGS = -I inc -g -mavx2 -no-pie -D _DEBUG -std=c++17 -O2 -Wall -Wextra -Weffc++

# Object files
OBJECTS = obj/main.o obj/hash_utils.o obj/handText.o obj/djb2.o

# Default target
all: init out

# Link
out: $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(CXXFLAGS) $(SANITIZER)

# Compile source files
obj/%.o: src/%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(SANITIZER)

obj/%.o: src/%.ASM
	nasm -f elf64 $< -o $@

# Clean
clean:
	rm -rf out obj/*.o 

init:
	mkdir -p obj