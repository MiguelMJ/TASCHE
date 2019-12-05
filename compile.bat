
g++ -mwin32 -DYY_NO_UNISTD_H -Ilib -Ithirdparty -std=c++11 src\expression.cpp src\expressionlexer.cpp src\expressionparser.cpp src\pattern.cpp src\patternlexer.cpp src\patternparser.cpp src\responses.cpp src\main.cpp -o TASCHE
