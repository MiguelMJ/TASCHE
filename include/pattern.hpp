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

#ifndef _PATTERN_HPP_
#define _PATTERN_HPP_

#include "expression.hpp"
#include "symboltable.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <forward_list>
#include <memory>
#include <exception>
#include <algorithm>

namespace cpt{
    typedef std::shared_ptr<struct st_pattern> pattern;
    typedef std::vector<std::string> string_list;
    typedef std::vector<pattern> pattern_list;
    /*
     * PATTERN
     */
    struct st_pattern{
        bool match(const std::string& str);
        virtual bool match(const std::string& str, int& pos) const = 0;
        virtual std::string compose() const = 0;
        virtual std::string toString() const = 0;
    };
    struct st_pattern_composed: st_pattern{
        pattern right, left;
        virtual bool match(const std::string& str, int& pos) const;
        virtual std::string compose() const;
        virtual std::string toString() const;
    };
    struct st_pattern_optional: st_pattern{
        pattern subpattern;
        virtual bool match(const std::string& str, int& pos) const;
        virtual std::string compose() const;
        virtual std::string toString() const;
    };
    struct st_pattern_plain: st_pattern{
        std::string frag;
        virtual bool match(const std::string& str, int& pos) const;
        virtual std::string compose() const;
        virtual std::string toString() const;
    };
    struct st_pattern_function: st_pattern{
        expression exp;
        virtual bool match(const std::string& str, int& pos) const;
        virtual std::string compose() const;
        virtual std::string toString() const;
    };
    struct st_pattern_multiple: st_pattern{
        pattern_list options;
        virtual bool match(const std::string& str, int& pos) const;
        virtual std::string compose() const;
        virtual std::string toString() const;
    };
    struct st_pattern_variable: st_pattern_plain{
        virtual bool match(const std::string& str, int& pos) const;
        virtual std::string compose() const;
        virtual std::string toString() const;
    };
    struct st_pattern_dynamic: st_pattern_composed{
        std::string id;
        virtual bool match(const std::string& str, int& pos) const;
        virtual std::string compose () const;
        virtual std::string toString() const;
    };
    pattern parsePattern(const std::string& str, bool verbose=false);
}

#endif
