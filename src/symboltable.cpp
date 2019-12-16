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

#include "symboltable.hpp"
#include <iostream>
namespace cpt{
namespace st{
    typedef std::map<std::string,std::string> table;
    int lastId = 0;
    namespace{
        std::stack<table> local_table;
        std::map<int,table> changesets;
        table symbol_table;
        void move(table& from, table& to){
            for(auto kv : from){
                to[kv.first] = kv.second;
            }
            from.clear();
        }
    }
    std::string get(const std::string& id){
        std::string ret;
        if(local_table.size() == 0){ // there are no local changes
            ret = symbol_table[id];
        }else{
            std::stack<table> aux;
            bool found = false;
            do{ // search from top to bottom
                aux.push(local_table.top());
                local_table.pop();
                auto lt = aux.top();
                auto it = lt.find(id);
                if(it != lt.end()){
                    ret = it->second;
                    found = true;
                }
            }while(!found && local_table.size() > 0);
            while(aux.size() > 0){ // we return stack of local tables to normal
                local_table.push(aux.top());
                aux.pop();
            }
            if(!found){
                ret = symbol_table[id];
            }
        }
        // std::cerr << "st: get " << id << " -> " << ret << std::endl;
        return ret;
    }
    void set(const std::string& id, const std::string& value){
        // std::cerr << "st: set " << id << " = " << value << std::endl;
        local_table.top()[id] = value;
    }
    void scope(){
        // std::cerr << "st: scoping" << std::endl;
        table t;
        /*if(local_table.size() > 0){
            for(auto pair : local_table.top()){
                t[pair.first] = pair.second;
            }
        }*/
        local_table.push(t);
    }
    void descope(){
        // std::cerr << "st: descoping" << std::endl;
        local_table.pop();
    }
    void add(int id){
        // // std::cerr << "st: adding:" << std::endl;
        for(auto pair : local_table.top()){
            // // std::cerr << '\t' << pair.first << "\t= " << pair.second << std::endl; 
        }
        table t;
        move(local_table.top(), t);
        changesets[id] = t;
    }
    void commit(){
        // std::cerr << "st: commiting" << std::endl;
        for(auto kv : changesets){
            /*for(auto p : kv.second){
                std::cerr << '\t' << p.first << "\t= " << p.second << std::endl;
            }*/
            move(kv.second,symbol_table);
        }
        changesets.clear();
    }
    int newId(){
        return ++lastId;
    }
}
}
