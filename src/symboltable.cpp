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
        if(local_table.size() == 0){
            ret = symbol_table[id];
        }else{
            auto lt = local_table.top();
            auto it = lt.find(id);
            if(it == lt.end()){
                ret = symbol_table[id];
            }else{
                ret = it->second;
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
        if(local_table.size() > 0){
            for(auto pair : local_table.top()){
                t[pair.first] = pair.second;
            }
        }
        local_table.push(t);
    }
    void descope(){
        // std::cerr << "st: descoping" << std::endl;
        local_table.pop();
    }
    void add(int id){
        // std::cerr << "st: adding:" << std::endl;
        for(auto pair : local_table.top()){
            // std::cerr << '\t' << pair.first << "\t= " << pair.second << std::endl; 
        }
        table t;
        move(local_table.top(), t);
        changesets[id] = t;
    }
    void commit(){
        // std::cerr << "st: commiting" << std::endl;
        for(auto kv : changesets){
            for(auto p : kv.second){
                // std::cerr << '\t' << p.first << "\t= " << p.second << std::endl;
            }
            move(kv.second,symbol_table);
        }
        changesets.clear();
    }
    int newId(){
        return ++lastId;
    }
}
}
