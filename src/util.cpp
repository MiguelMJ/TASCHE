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

#include "util.hpp"

namespace cpt{
    bool compare_case_insensitive (std::string s1, std::string s2){
        std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
        std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
        return s1 == s2;
    }
    void myassert(bool ass, const std::string& msg="Failed assert"){
        if(!ass){
            throw std::runtime_error(msg);
        }
    }
    std::string preprocesJSONFile(const std::string& filename){
        std::ifstream fin(filename.c_str());
        myassert(fin.good(), "Couldn't open "+filename);
        std::stringstream ret;
        char ch;
        bool str = false;
        ch = fin.get();
        while(!fin.eof()){
            if(ch == '\\'){
                ret << ch << (char)fin.get();
            }else if(str && ch=='\n'){
                ret << "\\n";
            }else{
                ret << ch;
                if(ch == '\"'){
                    str = !str;
                }
            }
            ch = fin.get();
        }
        fin.close();
        return ret.str();
    }
}
