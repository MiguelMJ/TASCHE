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
    } expressionST;
    typedef std::shared_ptr<expressionST> expression;
    struct expressionST_comp : expressionST{
        expression e1, e2;
        virtual std::string evaluate() const;
    };
    struct expressionST_neg : expressionST{
        expression exp;
        virtual bool evaluateBool() const;
        virtual std::string evaluate() const;
    };
    struct expressionST_text : expressionST{
        virtual std::string evaluate() const=0;
    };
    typedef struct : expressionST{
        virtual std::string evaluate() const;
        virtual int evaluateNum() const=0;
    } expressionST_numeric;
    typedef std::shared_ptr<expressionST_numeric> expressionNum;
    struct expressionST_number : expressionST_numeric{
        int value;
        virtual int evaluateNum() const;
    };
    struct expressionST_num_cast : expressionST_numeric{
        expression exp;
        virtual int evaluateNum() const;
    };
    struct expressionST_num_op : expressionST_numeric{
        exp::oper operation;
        expressionNum op1, op2;
        virtual int evaluateNum() const;
    };
    struct expressionST_string : expressionST_text{
        std::string value;
        virtual std::string evaluate() const;
    };
    struct expressionST_variable : expressionST_string{
        virtual std::string evaluate() const;
    };
    struct expressionST_str_op : expressionST_text{
        exp::oper operation;
        expression op1, op2;
        virtual std::string evaluate() const;
    };
    struct expressionST_asignation : expressionST{
        std::string id;
        expression value;
        virtual std::string evaluate() const;
    };
    expression parseExpression(const std::string& str,bool verbose=false);
}

#endif
