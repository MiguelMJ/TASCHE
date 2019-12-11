/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_EE_YY_INCLUDE_EXPRESSIONPARSER_HPP_INCLUDED
# define YY_EE_YY_INCLUDE_EXPRESSIONPARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef EE_YYDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define EE_YYDEBUG 1
#  else
#   define EE_YYDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define EE_YYDEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined EE_YYDEBUG */
#if EE_YYDEBUG
extern int ee_yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "lang/expression.bison" /* yacc.c:1909  */

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

#line 85 "include/expressionparser.hpp" /* yacc.c:1909  */

/* Token type.  */
#ifndef EE_YYTOKENTYPE
# define EE_YYTOKENTYPE
  enum ee_yytokentype
  {
    AND = 258,
    OR = 259,
    SNE = 260,
    SEQ = 261,
    EQ = 262,
    NE = 263,
    GE = 264,
    GT = 265,
    LE = 266,
    LT = 267,
    NUMBER = 268,
    VALUE = 269,
    STRVAR = 270,
    NUMVAR = 271,
    NOT = 272
  };
#endif

/* Value type.  */
#if ! defined EE_YYSTYPE && ! defined EE_YYSTYPE_IS_DECLARED

union EE_YYSTYPE
{
#line 52 "lang/expression.bison" /* yacc.c:1909  */

    int ival;
    std::string* strval;
    expressionST* expval;
    expressionST_numeric* expnumval;

#line 122 "include/expressionparser.hpp" /* yacc.c:1909  */
};

typedef union EE_YYSTYPE EE_YYSTYPE;
# define EE_YYSTYPE_IS_TRIVIAL 1
# define EE_YYSTYPE_IS_DECLARED 1
#endif


extern EE_YYSTYPE ee_yylval;

int ee_yyparse (void);

#endif /* !YY_EE_YY_INCLUDE_EXPRESSIONPARSER_HPP_INCLUDED  */
