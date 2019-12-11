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

#ifndef __RESPONSES_HPP__
#define __RESPONSES_HPP__

#include "pattern.hpp"
#include "expression.hpp"
#include "symboltable.hpp"
#include "util.hpp"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include "rapidjson/istreamwrapper.h"
#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <vector>
#include <exception>

namespace cpt{
    typedef std::shared_ptr<struct responseST> response;
    struct responseST{
        virtual bool respond(const std::string& str, std::ostream& out)=0;
    };
    struct SingleResponse : public responseST{
        pattern input;
        expression condition;
        virtual bool respond(const std::string& str, std::ostream& out)=0;
    };
    struct ResponseModule : public responseST{
        std::vector<response> responses;
        std::vector<response> defaultResponses;
        virtual bool respond(const std::string& str, std::ostream& out);
    };
    struct SimpleResponse : public SingleResponse{
        pattern output;
        virtual bool respond(const std::string& str, std::ostream& out);
    };
    struct RecursiveResponse : public SingleResponse{
        pattern new_answer;
        ResponseModule responses;
        virtual bool respond(const std::string& str, std::ostream& out);
    };
    void loadSpecs(const std::string& filename, bool verbose=false);
    std::string respond(const std::string& str);
    void launch();
    
}

#endif
