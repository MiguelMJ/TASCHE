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

#include "responses.hpp"

using namespace std;
using namespace rapidjson;

namespace cpt{
    pattern init;
    std::vector<response> responses;
    std::vector<response> defresponses;
    void loadSpecs(const std::string& filename){
        try{
            ifstream fin(filename.c_str());
            IStreamWrapper isw(fin);
            
            Document d;
            d.ParseStream(isw);
            fin.close();
            init = parsePattern(d["init"].GetString());
            Value r = d["responses"].GetArray();
            for(auto it = r.Begin(); it != r.End(); it++){
                auto target = &responses;
                pattern input = nullptr;
                if(it->HasMember("input")){
                    input = parsePattern((*it)["input"].GetString());
                }else{
                    target = &defresponses;
                }
                if(it->HasMember("responses")){
                    auto res = (*it)["responses"].GetArray();
                    for (auto itr = res.Begin(); itr != res.End(); itr++){
                        response r;
                        r.input = input;
                        r.condition = (*itr)["condition"].GetString();
                        r.output = parsePattern((*itr)["output"].GetString());
                        target->push_back(r);
                    }
                }else{
                    response r;
                    r.input = input;
                    r.condition = (*it)["condition"].GetString();
                    r.output = parsePattern((*it)["output"].GetString());
                    target->push_back(r);
                }
                /*
                response r;
                r.condition = (*it)["condition"].GetString();
                r.output = parsePattern((*it)["output"].GetString());
                if(it->HasMember("input")){
                    r.input = parsePattern((*it)["input"].GetString());
                    responses.push_back(r);
                }else{
                    defresponses.push_back(r);
                } 
                */
            }
        }catch(std::exception& e){
            #ifdef DEBUG
            cerr << "\e[38;2;250;0;0m" << e.what() << "\e[0m" << endl;
            #else
            cerr << e.what() << endl;
            #endif
        }
    }
    bool b(const std::string& s){
        bool ret;
        try{
            ret = stoi(s) != 0;
        }catch(std::exception& e){
            ret = !s.empty();
        }
        return ret;
    }
    void respond(const std::string& str){
        bool matched = false;
        std::string res;
        for(auto r : responses){
            if(r.input->match(str) && b(parseExpression(r.condition))){
                matched = true;
                res = r.output->compose();
                if(!res.empty()){
                    cout << res << endl;
                }
            }
        }
        if(!matched){
            for(auto r : defresponses){
                if(b(parseExpression(r.condition))){
                    res = r.output->compose();
                    if(!res.empty()){
                        cout << res << endl;
                    }
                }
            }
        }
        updateSymbolTable();
    }
    void launch(){
        symbol_table["_TA_RUNNING_"] = "1";
        cout << init->compose();
        while(b(symbol_table["_TA_RUNNING_"]) && !cin.eof()){
            try{
                string str;
                cout << ">";
                getline(cin,str);
                respond(str);
            }catch(exception& e){
                #ifdef DEBUG
                cerr << "\e[38;2;250;0;0m" << e.what() << "\e[0m" << endl;
                #else
                cerr << e.what() << endl;
                #endif
            }
        }
    }
}
