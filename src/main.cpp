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

#ifdef DEBUG
#include "patternparser.hpp"
#include "expressionparser.hpp"
#endif

#include "pattern.hpp"
#include "expression.hpp"
#include "responses.hpp"
#include <exception>

#include "rapidjson/document.h"
using namespace cpt;
using namespace std;
int main(int argc, char** argv){
    #ifdef DEBUG
    ee_yydebug = 1;
    pp_yydebug = 1;
    #endif
    bool verbose = false;
    // options
    int argi = 1;
    string option;
    bool option_recognized = true;
    while(argi < argc && option_recognized){
        option = argv[argi];
        if(option[0] == '-'){
            argi++;
            if(option == "-v"){
                verbose = true;
                cerr << "mode verbose" << endl;
            }else{
                cerr << "unknown option " << option;
            }
        }else{
            option_recognized = false;
        }
    }
    // launch
    try{
        if(argi < argc){
            for(int i = argi; i < argc; i++){
                loadSpecs(argv[i], verbose);
            }
            launch();
        }else{
            cout << "Provide specification files" << endl;
        }
    }catch(exception& e){
        #ifdef DEBUG
        cerr << "\e[38;2;250;0;0m" << e.what() << "\e[0m" << endl;
        #else
        cerr << e.what() << endl;
        #endif
    }
    return 0;
}
