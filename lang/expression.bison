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
#include "symboltable.hpp"
using namespace cpt;
extern expression parsedExpression;
extern int ee_yylex();
void ee_yyerror(const char* msg);
}
%{
#include "expression.hpp"
using namespace cpt;
st_expression* makestrop(st_expression* e1,exp::oper o,st_expression* e2){
    auto exstrop = new struct st_expression_str_op;
    exstrop -> operation = o;
    exstrop -> op1 = expression(e1);
    exstrop -> op2 = expression(e2);
    return exstrop;
}
st_expression_numeric* makenumop(st_expression_numeric* e1,exp::oper o,st_expression_numeric* e2){
    auto exnumop = new struct st_expression_num_op;
    exnumop -> operation = o;
    exnumop -> op1 = expressionNum(e1);
    exnumop -> op2 = expressionNum(e2);
    return exnumop;
}
%}
%define api.prefix {ee_yy}
%union{
    int ival;
    std::string *strval;
    std::vector<expression> *vecval;
    st_expression* expval;
    st_expression_numeric* expnumval;
}
%token <void> AND OR SNE SEQ EQ NE GE GT LE LT 
%token <ival> NUMBER
%token <strval> VALUE STRVAR NUMVAR USERFUNC

%type <void> axiom
%type <expval> program
%type <expval> exp
%type <expnumval> nexp
%type <vecval> arglist arglist2

%left ';'
%left OR
%left AND
%right NOT
%left EQ NE GE GT LE LT
%left SEQ SNE
%left '+' '-'
%left '*'
%left '/' '%'
%right '^'
%left '('

%%
axiom : program {parsedExpression = expression($1);}
      ;
program : exp            {$$ = $1;}
        | STRVAR '=' exp {auto exas = new st_expression_asignation;
                          exas -> id = *$1;
                          exas -> value = expression($3);
                          $$ = exas;
                          delete $1;
                         }
        | NUMVAR '=' exp {auto excast = new st_expression_num_cast;
                          excast -> exp = expression($3);
                          auto exas = new st_expression_asignation;
                          exas -> id = *$1;
                          exas -> value = expression(excast);
                          $$ = exas;
                          delete $1;
                         }
        | program ';' program {auto excomp = new st_expression_comp;
                               excomp -> e1 = expression($1);
                               excomp -> e2 = expression($3);
                               $$ = excomp;
                                }
        | {$$ = new st_expression_string;}
        ;
exp : VALUE {auto exstr = new st_expression_string;
             exstr -> value = *$1;
             $$ = exstr;
             delete $1;
            }
    | nexp  {$$ = $1;}
    | NOT exp {auto exne = new st_expression_neg;
               exne->exp = expression($2);
               $$ = exne;
                }
    | exp AND exp {$$ = makestrop($1,exp::oper::AND,$3);}
    | exp  OR exp {$$ = makestrop($1,exp::oper::OR,$3);}
    | exp SEQ exp {$$ = makestrop($1,exp::oper::SEQ,$3);}
    | exp SNE exp {$$ = makestrop($1,exp::oper::SNE,$3);}
    | STRVAR      {auto exvar = new st_expression_variable;
                   exvar -> value = *$1;
                   $$ = exvar;
                   delete $1;
                   }
    | USERFUNC '(' arglist ')' {
                    auto exuf = new st_expression_userfunc;
                    exuf->value = *$1;
                    exuf->args = arg_list($3);
                    $$ = exuf;
                    delete $1;
                }
    ;
arglist :  arglist2 {$$ = $1;}
        | {$$ = new std::vector<expression>;}
        ;
arglist2 : arglist2 ',' exp {$1->push_back(expression($3)); $$ = $1;}
         | exp {$$ = new std::vector<expression>; $$->push_back(expression($1));}
         ;
nexp: NUMBER        {auto exnum = new st_expression_number;
                     exnum -> value = $1;
                     $$ = exnum;
                    }
    | '(' exp ')'   {auto excast = new st_expression_num_cast;
                     excast -> exp = expression($2);
                     $$ = excast;
                    }
    | nexp '+' nexp {$$ = makenumop($1,exp::oper::SUM, $3);}
    | nexp '-' nexp {$$ = makenumop($1,exp::oper::DIF, $3);}
    | nexp '*' nexp {$$ = makenumop($1,exp::oper::MUL, $3);}
    | nexp '/' nexp {$$ = makenumop($1,exp::oper::DIV, $3);}
    | nexp '%' nexp {$$ = makenumop($1,exp::oper::MOD, $3);}
    | nexp '^' nexp {$$ = makenumop($1,exp::oper::POW, $3);}
    | nexp EQ nexp  {$$ = makenumop($1,exp::oper::EQ, $3);}
    | nexp NE nexp  {$$ = makenumop($1,exp::oper::NE, $3);}
    | nexp GE nexp  {$$ = makenumop($1,exp::oper::GE, $3);}
    | nexp GT nexp  {$$ = makenumop($1,exp::oper::GT, $3);}
    | nexp LE nexp  {$$ = makenumop($1,exp::oper::LE, $3);}
    | nexp LT nexp  {$$ = makenumop($1,exp::oper::LT, $3);}
    | NUMVAR        {auto exvar = new st_expression_variable;
                     exvar -> value = *$1;
                     auto excast = new st_expression_num_cast;
                     excast -> exp = expression(exvar);
                     $$ = excast;
                     delete $1;
                    }
    ;

%%
void ee_yyerror(const char* msg){
    throw std::runtime_error("expression parser:"+std::string(msg));
}

void set_input_string(const char* in);
void end_lexical_scan(void);

