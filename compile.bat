REM pattern library
REM bison --defines=pattern/patternparser.hpp pattern/pattern.y -o pattern/patternparser.cpp &&
REM flex -o pattern/patternlexer.cpp pattern/pattern.l &&
REM expression library
REM bison --defines=expression/expressionparser.hpp expression/expression.y -o expression/expressionparser.cpp &&
REM flex -o expression/expressionlexer.cpp expression/expression.l &&

g++ -mwin32 -Ilib -Ithirdparty -std=c++11 src\\*.cpp -o TASCHE
