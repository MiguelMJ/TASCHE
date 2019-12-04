%{
/*
 * MIT License
 * 
 * Copyright (c) 2019 Miguel Mejía J
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */ 

#ifdef DEBUG
#include <iostream>
#endif
#include "expression.hpp"
#include "expressionparser.hpp"
#include <sstream>
using namespace cpt;
typedef struct yy_buffer_state * YY_BUFFER_STATE;
extern int yyparse();
extern YY_BUFFER_STATE yy_scan_string(char * str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
std::string parsedExpression;
%}
%option noyywrap
%option prefix="ee_yy"
%x STRING

ID [a-zA-Z_][a-zA-Z_0-9]*

%%

%{
std::stringstream token;
%}

<STRING>{
    \\b     {token<<'\b';}
    \\f     {token<<'\f';}
    \\n     {token<<'\n';}
    \\r     {token<<'\r';}
    \\t     {token<<'\t';}
    \\\"    {token<<'\"';}
    \\\\    {token<<'\\';}
    \\\'     {token<<'\'';}
    \'\'    {BEGIN(INITIAL);
            auto ret = new std::string(token.str());
            token.str("");
            ee_yylval.strval = ret;
            return VALUE;
            }
    .|\n       {token << yytext;}
}
\'\'  {
      token.str("");
      BEGIN(STRING);
      }

[0-9]+  {ee_yylval.ival = atoi(yytext);
         return NUMBER;
        }
\@{ID}     {
            auto ret = new std::string(yytext);
            *ret = ret->substr(1);
            ee_yylval.strval = ret;
            return STRVAR;
           }
\#{ID}     {
            auto ret = new std::string(yytext);
            *ret = ret->substr(1);
            ee_yylval.strval = ret;
            return NUMVAR;
           }
[+\-*/^%=;]  {return yytext[0];}
!          {return NOT;}
&&         {return AND;}
"||"       {return OR;}
==         {return SEQ;}
!=         {return SNE;}
-eq        {return EQ;}
-ne        {return NE;}
-lt        {return LT;}
-gt        {return GT;}
-le        {return LE;}
-ge        {return GT;}

.|\n       {}

%%
void ee_set_input_string(const char* in) {
  yy_scan_string(in);
}

void ee_end_lexical_scan(void) {
  yy_delete_buffer(YY_CURRENT_BUFFER);
}
namespace cpt{
    std::string parseExpression(const std::string& str){
        #ifdef DEBUG
        std::cout << "\e[38;2;250;250;0mparseExpression: " << str << "\e[0m" << std::endl;
        #endif
        ee_set_input_string(str.c_str());
        ee_yyparse();
        ee_end_lexical_scan();
        #ifdef DEBUG
        std::cout << "\e[38;2;0;250;0mSuccesfully parsed expression: " << str << " as \"" << parsedExpression << "\"\e[0m" << std::endl;
        #endif
        return parsedExpression;
    }
}
