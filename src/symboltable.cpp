#include "symboltable.hpp"
#include <iostream>
namespace cpt{
namespace st{
    typedef std::map<std::string,std::string> table;
    namespace{
        table local_table;
        table changes_table;
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
        auto it = local_table.find(id);
        if(it == local_table.end()){
            ret = symbol_table[id];
        }else{
            ret = it->second;
        }
        return ret;
    }
    void set(const std::string& id, const std::string& value){
        local_table[id] = value;
    }
    void add(){
        move(local_table, changes_table);
    }
    void discard(){
        local_table.clear();
    }
    void commit(){
        move(changes_table, symbol_table);
    }
}
}
