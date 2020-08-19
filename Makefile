EXEC = tasche
CXX = g++
CXXFLAGS = -O3 -std=c++11 $(INCLUDES)
CC = $(CXX)
CFLAGS = $(CXXFLAGS)

INCLUDES = -Iinclude -Ithirdparty

SRC = $(EXEC).cpp $ $(wildcard src/*.cpp)

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(SRC) lang
	$(CXX) $(CXXFLAGS) *.cpp src/*.cpp -o $@

lang: patterns expressions

patterns:
	bison --defines=include/pattern.bison.hpp src/pattern.bison -o src/pattern.bison.cpp
	flex --nounistd -o src/pattern.flex.cpp src/pattern.flex
	
expressions:
	bison --defines=include/expression.bison.hpp src/expression.bison -o src/expression.bison.cpp
	flex --nounistd -o src/expression.flex.cpp src/expression.flex
