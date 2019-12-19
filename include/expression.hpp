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

#ifndef __EXPRESSION_HPP__
#define __EXPRESSION_HPP__

#include <memory>
#include <string>
#include <vector>
#include <exception>
#include "symboltable.hpp"
#include "util.hpp"
namespace cpt{
    namespace exp{
        typedef enum {
            SUM, DIF, MUL, DIV, MOD, POW,
            EQ, NE, GE, GT, LE, LT,
            AND, OR, SEQ, SNE
        } oper;
    }
    typedef struct {
        virtual bool evaluateBool() const;
        virtual std::string evaluate() const=0;
    } st_expression;
    
    typedef std::shared_ptr<st_expression> expression;
    typedef std::shared_ptr<std::vector<expression> > arg_list;
    typedef std::string (*userfunc)(const std::vector<std::string>&);
    extern std::map<std::string, userfunc> functions;
    
    struct st_expression_comp : st_expression{
        expression e1, e2;
        virtual std::string evaluate() const;
    };
    struct st_expression_neg : st_expression{
        expression exp;
        virtual bool evaluateBool() const;
        virtual std::string evaluate() const;
    };
    struct st_expression_text : st_expression{
        virtual std::string evaluate() const=0;
    };
    typedef struct : st_expression{
        virtual std::string evaluate() const;
        virtual int evaluateNum() const=0;
    } st_expression_numeric;
    typedef std::shared_ptr<st_expression_numeric> expressionNum;
    struct st_expression_number : st_expression_numeric{
        int value;
        virtual int evaluateNum() const;
    };
    struct st_expression_num_cast : st_expression_numeric{
        expression exp;
        virtual int evaluateNum() const;
    };
    struct st_expression_num_op : st_expression_numeric{
        exp::oper operation;
        expressionNum op1, op2;
        virtual int evaluateNum() const;
    };
    struct st_expression_string : st_expression_text{
        std::string value;
        virtual std::string evaluate() const;
    };
    struct st_expression_variable : st_expression_string{
        virtual std::string evaluate() const;
    };
    struct st_expression_userfunc : st_expression_string{
        arg_list args;
        virtual std::string evaluate() const;
    };
    struct st_expression_str_op : st_expression_text{
        exp::oper operation;
        expression op1, op2;
        virtual std::string evaluate() const;
    };
    struct st_expression_asignation : st_expression{
        std::string id;
        expression value;
        virtual std::string evaluate() const;
    };
    expression parseExpression(const std::string& str,bool verbose=false);
}

#endif
