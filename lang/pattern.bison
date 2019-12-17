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

#include "pattern.hpp"
using namespace cpt;
extern cpt::pattern parsedPattern;
extern int pp_yylex();
void pp_yyerror(const char* msg);
}
%define api.prefix {pp_yy}
%union{
    char strval[50];
    char bigstr[500];
    struct st_pattern* paval;
    pattern_list* plval;
}
%token <paval> ATOMIC
%token <bigstr> SCRIPT
%token <strval> DYNAMIC

%type <void> finalpattern
%type <paval> patterntk
%type <paval> patterntklist
%type <plval> pattern_options
%type <plval> pattern_options2

%left '|'
%left '{' '[' '(' ATOMIC

%%
finalpattern : patterntklist {parsedPattern = pattern($1);}
             |   {
                    auto spp = new st_pattern_plain;
                    spp -> frag = "";
                    parsedPattern = pattern(spp);
                }
             ;
patterntklist : patterntk patterntklist {
                            auto spc = new st_pattern_composed;
                            spc->left = pattern($1);
                            spc->right = pattern($2);
                            $$ = spc;
                            }
               | DYNAMIC patterntklist {
                            auto spd = new st_pattern_dynamic;
                            spd->id = $1;
                            spd -> shortest = $1[0]=='.';
                            if(spd -> shortest){
                                spd -> id = spd -> id.substr(1);
                            }
                            spd->right = pattern($2);   
                            $$ = spd;
                            }
               | patterntk  {$$ = $1;}
               | DYNAMIC    {
                            auto spd = new st_pattern_dynamic;
                            spd -> id = $1;
                            spd -> shortest = $1[0]=='.';
                            if(spd -> shortest){
                                spd -> id = spd -> id.substr(1);
                            }
                            spd -> right = nullptr;
                            $$ = spd;
                            }
                | '[' patterntklist ']' patterntklist {
                            auto spo = new st_pattern_optional;
                            spo -> left = pattern($2);
                            spo -> right = pattern($4);
                            $$ = spo;
                            }
                | '[' patterntklist ']' {
                            auto spo = new st_pattern_optional;
                            spo -> left = pattern($2);
                            spo -> right = nullptr;
                            $$ = spo;
                            }
               ;
patterntk   : SCRIPT    {
                        auto spf = new st_pattern_function;
                        spf -> exp = parseExpression($1,false);
                        $$ = spf;
                        }
            | '(' pattern_options ')'   {
                            auto spm = new st_pattern_multiple;
                            spm -> options = *$2;
                            $$ = spm;
                            delete $2;
                            }
            | ATOMIC    {$$ = $1;}
            ;
pattern_options  : patterntklist '|' patterntklist pattern_options2 {
                                    $4->push_back(pattern($3));
                                    $4->push_back(pattern($1));
                                    $$ = $4;
                                    }
                 ;
pattern_options2 : '|' patterntklist pattern_options2 {
                                    $3->push_back(pattern($2)); 
                                    $$ = $3;
                                    }
                 | {$$ = new pattern_list;}
                 ;

                

%%
void pp_yyerror(const char* msg){
    throw std::runtime_error("pattern parser:"+std::string(msg));
}

void set_input_string(const char* in);
void end_lexical_scan(void);

