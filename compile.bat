@echo off
g++ -mwin32 -std=c++11 -DYY_NO_UNISTD_H -Iinclude -Ithirdparty src\expression.cpp src\expressionlexer.cpp src\expressionparser.cpp src\pattern.cpp src\patternlexer.cpp src\patternparser.cpp src\responses.cpp src\symboltable.cpp src\util.cpp src\main.cpp -o TASCHE
