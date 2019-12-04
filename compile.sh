#!/bin/bash
# pattern library
bison --defines=lib/patternparser.hpp src/pattern.y -o src/patternparser.cpp &&
flex -o src/patternlexer.cpp src/pattern.l &&
# expression library
bison --defines=lib/expressionparser.hpp src/expression.y -o src/expressionparser.cpp &&
flex -o src/expressionlexer.cpp src/expression.l &&

g++ -Ilib -Ithirdparty -std=c++11 src/*.cpp -o TASCHE
