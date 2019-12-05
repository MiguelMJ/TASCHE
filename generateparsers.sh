#!/bin/bash
# patterns
bison --defines=include/patternparser.hpp lang/pattern.bison -o src/patternparser.cpp &&
flex --nounistd -o src/patternlexer.cpp lang/pattern.flex
# expressions
bison --defines=include/expressionparser.hpp lang/expression.bison -o src/expressionparser.cpp &&
flex --nounistd -o src/expressionlexer.cpp lang/expression.flex
