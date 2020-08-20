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
#include "pattern.hpp"
#include "pattern.bison.hpp"
#include <sstream>
using namespace cpt;
typedef struct yy_buffer_state * YY_BUFFER_STATE;
extern int yyparse();
extern YY_BUFFER_STATE yy_scan_string(char * str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
pattern parsedPattern;
std::string prepare(std::string st);
%}
%option always-interactive
%option noyywrap
%option prefix="pp_yy"
%x STRING
%x SCR

RESERVED [\'\"\[\]\{\}\(\)\$\>\|]
NOTRESERVED [^\'\"\[\]\{\}\(\)\$\>\|]
ID [a-zA-Z_][a-zA-Z0-9_]*

%%

%{
std::stringstream token;
%}

<STRING>{
    \\b     {token << '\b';}
    \\f     {token << '\f';}
    \\n     {token << '\n';}
    \\r     {token << '\r';}
    \\t     {token << '\t';}
    \"      {token << '\"';}
    \\\\    {token << '\\';}
    \'\'     {BEGIN(INITIAL);
             auto aux = new struct st_pattern_plain;
             aux -> frag = token.str();
             pp_yylval.paval = aux;
             return ATOMIC;
            }
    .|\n       {token << yytext;}
}
<SCR>{
    \\\} {token << "}";}
    \}   {BEGIN(INITIAL);
          strcpy(pp_yylval.bigstr,token.str().c_str());
          return SCRIPT;
         }
    .|\n    {token << yytext;}
}
\{   {token.str("");
      BEGIN(SCR);
     }
\'\' {
        token.str("");
        BEGIN(STRING);
     }
({NOTRESERVED}(\\.)?)+   {
                auto aux = new struct st_pattern_plain;
                aux -> frag = prepare(yytext);
                pp_yylval.paval = aux;
                return ATOMIC;
                }
"$"{ID}      {
            auto aux = new struct st_pattern_variable;
            aux -> frag = yytext;
            aux -> frag = aux -> frag.substr(1);
            pp_yylval.paval = aux;
            return ATOMIC;
            }
">"\.?{ID}      {
            std::string aux(yytext);
            aux = aux.substr(1);
            strcpy(pp_yylval.strval,aux.c_str());
            return DYNAMIC;
            }
{RESERVED}  {return yytext[0];}


%%
void pp_set_input_string(const char* in) {
  yy_scan_string(in);
}

void pp_end_lexical_scan(void) {
  yy_delete_buffer(YY_CURRENT_BUFFER);
}
std::string prepare(std::string str){
    for(auto it = str.begin(); it != str.end(); it++){
        if(*it == '\\'){
            it = str.erase(it);
            it++;
        }
    }
    return str;
}
namespace cpt{
    pattern parsePattern(const std::string& str, bool verbose){
        #ifdef DEBUG
        std::cout << "\e[38;2;250;250;0mparsePattern: " << str << "\e[0m" << std::endl;
        #endif
        if(verbose){
            std::cerr << "parse pattern: " << str << std::endl;
        }
        pp_set_input_string(str.c_str());
        pp_yyparse();
        pp_end_lexical_scan();
        #ifdef DEBUG
        std::cout << "\e[38;2;0;250;0m" << "Succesfully parsed pattern: " << parsedPattern->toString() << "\e[0m" << std::endl;
        #endif
        return parsedPattern;
    }
}
