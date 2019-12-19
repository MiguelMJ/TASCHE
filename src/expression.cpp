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
namespace cpt{
    std::map<std::string, userfunc> functions;
    void semantic_error(){
        throw std::runtime_error("semantic error in expression");
    }
    bool b(const std::string& str){
        bool ret;
        try{
            ret = std::stoi(str) != 0;
        }catch(std::exception& e){
            ret = !str.empty();
        }
        return ret;
    }
    bool st_expression::evaluateBool()const{
        return b(evaluate());
    }
    std::string st_expression_comp::evaluate()const{
        e1->evaluate();
        return e2->evaluate();
    }
    bool st_expression_neg::evaluateBool()const{
        return !b(evaluate());
    }
    std::string st_expression_neg::evaluate()const{
        return exp->evaluate();
    }
    std::string st_expression_numeric::evaluate()const{
        return std::to_string(evaluateNum());
    }
    int st_expression_number::evaluateNum()const{
        return value;
    }
    int st_expression_num_cast::evaluateNum()const{
        int ret;
        try{
            ret = std::stoi(exp->evaluate());
        }catch(std::exception& e){
            ret = 0;
        }
        return ret;
    }
    int st_expression_num_op::evaluateNum()const{
        int v1, v2, ret;
        v1 = op1->evaluateNum();
        v2 = op2->evaluateNum();
        switch(operation){
            case exp::oper::SUM:
                ret = v1 + v2;
            break;
            case exp::oper::DIF:
                ret = v1 - v2;
            break;
            case exp::oper::MUL:
                ret = v1 * v2;
            break;
            case exp::oper::DIV:
                ret = v1 / v2;
            break;
            case exp::oper::MOD:
                ret = v1 % v2;
            break;
            case exp::oper::POW:
                ret = 1;
                while(v2 > 0){
                    ret *= v1;
                    v2--;
                }
            break;
            case exp::oper::EQ:
                ret = v1 == v2? 1: 0;
            break;
            case exp::oper::NE:
                ret = v1 != v2? 1: 0;
            break;
            case exp::oper::GE:
                ret = v1 >= v2? 1: 0;
            break;
            case exp::oper::GT:
                ret = v1 > v2? 1: 0;
            break;
            case exp::oper::LE:
                ret = v1 <= v2? 1: 0;
            break;
            case exp::oper::LT:
                ret = v1 < v2? 1: 0;
            break;
            default:
                semantic_error();
        }
        return ret;
    }
    std::string st_expression_string::evaluate() const{
        return value;
    }
    std::string st_expression_userfunc::evaluate() const{
        std::vector<std::string> argv;
        for(auto e : *args){
            argv.push_back(e->evaluate());
        }
        return functions[value](argv);
    }
    std::string st_expression_variable::evaluate() const{
        return st::get(value);
    }
    std::string st_expression_str_op::evaluate() const{
        std::string ret;
        switch (operation){
            case exp::oper::AND:
                ret = op1->evaluateBool() && op2->evaluateBool()? "1": "0";
                break;
            case exp::oper::OR:
                ret = op1->evaluateBool() || op2->evaluateBool()? "1": "0";
                break;
            case exp::oper::SEQ:
                ret = compare_case_insensitive(op1->evaluate(), op2->evaluate())? "1": "0";
                break;
            case exp::oper::SNE:
                ret = compare_case_insensitive(op1->evaluate(), op2->evaluate())? "0": "1";
                break;
            default:
                semantic_error();
        }
        return ret;
    }
    std::string st_expression_asignation::evaluate()const{
        st::set(id,value->evaluate());
        return "";
    }
}
