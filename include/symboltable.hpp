#ifndef _SYMBOL_TABLE_HPP_
#define _SYMBOL_TABLE_HPP_

#include <map>
#include <string>
namespace cpt{
namespace st{
    std::string get(const std::string& id);
    void set(const std::string& id, const std::string& value);
    void add();
    void discard();
    void commit();
}
}
#endif
