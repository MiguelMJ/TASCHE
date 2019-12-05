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

#ifndef YY_PP_YY_INCLUDE_PATTERNPARSER_HPP_INCLUDED
# define YY_PP_YY_INCLUDE_PATTERNPARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef PP_YYDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define PP_YYDEBUG 1
#  else
#   define PP_YYDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define PP_YYDEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined PP_YYDEBUG */
#if PP_YYDEBUG
extern int pp_yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "lang/pattern.bison" /* yacc.c:1909  */

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

#line 84 "include/patternparser.hpp" /* yacc.c:1909  */

/* Token type.  */
#ifndef PP_YYTOKENTYPE
# define PP_YYTOKENTYPE
  enum pp_yytokentype
  {
    ATOMIC = 258,
    SCRIPT = 259,
    DYNAMIC = 260
  };
#endif

/* Value type.  */
#if ! defined PP_YYSTYPE && ! defined PP_YYSTYPE_IS_DECLARED

union PP_YYSTYPE
{
#line 33 "lang/pattern.bison" /* yacc.c:1909  */

    char strval[50];
    char bigstr[500];
    struct st_pattern* paval;
    pattern_list* plval;

#line 109 "include/patternparser.hpp" /* yacc.c:1909  */
};

typedef union PP_YYSTYPE PP_YYSTYPE;
# define PP_YYSTYPE_IS_TRIVIAL 1
# define PP_YYSTYPE_IS_DECLARED 1
#endif


extern PP_YYSTYPE pp_yylval;

int pp_yyparse (void);

#endif /* !YY_PP_YY_INCLUDE_PATTERNPARSER_HPP_INCLUDED  */
