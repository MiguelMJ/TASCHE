%code requires{
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

#include "expression.hpp"
using namespace cpt;
extern std::string parsedExpression;
extern int ee_yylex();
void ee_yyerror(const char* msg);
}
%{
#include <string>
#include <exception>
bool b(const std::string& s){
    bool ret;
    try{
        ret = 0 != std::stoi(s);
    }catch(std::exception& e){
        ret = !s.empty();
    }
    return ret;
}
std::string s(bool b){
    return b ? "1" : "0";
}
int pow(int a, int b){
    int ret = 1;
    while(b>0){
        ret*=a;
        b--;
    }
    return ret;
}
%}
%define api.prefix {ee_yy}
%union{
    int ival;
    std::string* strval;
}
%token <void> AND OR SNE SEQ EQ NE GE GT LE LT 
%token <ival> NUMBER
%token <strval> VALUE STRVAR NUMVAR

%type <void> axiom
%type <strval> program
%type <strval> exp
%type <ival> nexp

%left ';'
%right NOT
%nonassoc AND
%nonassoc OR
%left SEQ SNE
%left EQ NE GE GT LE LT
%right'^'
%left '/' '%'
%nonassoc '*'
%nonassoc '+' '-'

%%
axiom : program {parsedExpression = *$1;
                 delete $1;
                }
      ;
program : exp            {$$ = $1;}
        | STRVAR '=' exp {  cpt::changes_table[*$1] = *$3;
                            $$ = $3; delete $1;
                            }
        | NUMVAR '=' exp {  auto v = std::to_string(std::stoi(*$3));
                            cpt::changes_table[*$1] = v;
                            $$ = $3; delete $1;
                            }
        | program ';' program {$$ = $3; delete $1;}
        ;
exp : VALUE {$$ = $1;}
    | nexp  {$$ = new std::string(std::to_string($1));}
    | NOT exp {$$ = new std::string(s(!b(*$2))); delete $2;}
    | exp AND exp {
                   $$ = new std::string(s(b(*$1) && b(*$3)));
                   delete $1; delete $3;
                   }
    | exp  OR exp {
                   $$ = new std::string(s(b(*$1) || b(*$3)));
                   delete $1; delete $3;
                   }
    | exp SEQ exp {
                   $$ = new std::string(s(*$1 == *$3));
                   delete $1; delete $3;
                   }
    | exp SNE exp {
                   $$ = new std::string(s(*$1 != *$3));
                   delete $1; delete $3;
                  }
    | STRVAR      {$$ = new std::string(cpt::symbol_table[*$1]); delete $1;}
    ;
nexp: NUMBER        {$$ = $1;}
    | nexp '+' nexp {$$ = $1 + $3;}
    | nexp '-' nexp {$$ = $1 - $3;}
    | nexp '*' nexp {$$ = $1 * $3;}
    | nexp '/' nexp {$$ = $1 / $3;}
    | nexp '%' nexp {$$ = $1 % $3;}
    | nexp '^' nexp {$$ = pow($1,$3);}
    | nexp EQ nexp  {$$ = $1 == $3 ? 1 : 0;}
    | nexp NE nexp  {$$ = $1 != $3 ? 1 : 0;}
    | nexp GE nexp  {$$ = $1 >= $3 ? 1 : 0;}
    | nexp GT nexp  {$$ = $1  > $3 ? 1 : 0;}
    | nexp LE nexp  {$$ = $1 <= $3 ? 1 : 0;}
    | nexp LT nexp  {$$ = $1  < $3 ? 1 : 0;}
    | NUMVAR        {$$ = std::stoi(cpt::symbol_table[*$1]); delete $1;}
    ;

%%
void ee_yyerror(const char* msg){
    throw std::runtime_error("expression parser:"+std::string(msg));
}

void set_input_string(const char* in);
void end_lexical_scan(void);

