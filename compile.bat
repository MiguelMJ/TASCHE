@echo off
g++ -mwin32 -std=c++11 -DYY_NO_UNISTD_H -Ilib -Ithirdparty src\expression.cpp src\expressionlexer.cpp src\expressionparser.cpp src\pattern.cpp src\patternlexer.cpp src\patternparser.cpp src\responses.cpp src\main.cpp -o TASCHE
