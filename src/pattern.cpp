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

#include "pattern.hpp"

namespace cpt{
    bool compare_case_insensitive (std::string s1, std::string s2){
        std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
        std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
        return s1 == s2;
    }
    std::map<std::string, std::string> symbol_table;
    std::map<std::string, std::string> changes_table;
    std::map<std::string, std::string> local_table;
    bool st_pattern::match(const std::string& str){
        int pos = 0;
        return match(str,pos) && pos == str.size(); 
    }
    bool st_pattern_composed::match(const std::string& str, int& pos) const{
        return left->match(str, pos) && right->match(str,pos);
    }
    bool st_pattern_plain::match(const std::string& str, int& pos) const{
        bool matched = false;
        int size = frag.size();
        std::string localstr = str.substr(pos,size);
        matched = compare_case_insensitive(frag, localstr);
        if(matched) pos += size;
        return matched;
    }
    bool st_pattern_optional::match(const std::string& str, int& pos) const{
        int oldpos = pos;
        bool matched = subpattern->match(str,pos);
        if(!matched){
            pos = oldpos;
        }
        return true;
    }
    bool st_pattern_function::match(const std::string& str, int& pos) const{
        std::string value = compose();
        bool matched = compare_case_insensitive(value, str.substr(pos,value.size()));
        if(matched){
            pos += value.size();
        }
        return matched;
    }
    bool st_pattern_multiple::match(const std::string& str, int& pos) const{
        int oldpos = pos;
        bool matched;
        for(auto p: options){
            matched = p->match(str,pos);
            if(!matched){
                pos = oldpos;
            }else{
                break;
            }
        }
        return matched;
    }
    bool st_pattern_variable::match(const std::string& str, int& pos) const{
        std::string value = local_table[str];
        bool matched = compare_case_insensitive(value, str.substr(pos,value.size()));
        if(matched){
            pos += value.size();
        }
        return matched;
    }
    bool st_pattern_dynamic::match(const std::string& str, int& pos) const{
        bool matched;
        if(right == nullptr){
            local_table[id] = str.substr(pos);
            pos = str.size();
            matched = true;
        }else{
            matched = false;
            int oldpos = pos;
            int trynum = 1;
            int size = str.size();
            while(!matched && size-trynum != pos){
                pos = size-trynum;
                matched = right->match(str,pos);
                if(matched){
                    local_table[id] = str.substr(oldpos,pos-oldpos-trynum);
                }else{
                    pos = oldpos;
                    trynum++;
                }
            }
        }
        return matched;
    }
    std::random_device rand;
    std::string st_pattern_composed::compose () const{
        return left->compose() + right->compose();
    }
    std::string st_pattern_plain::compose () const{
        return frag;
    }
    std::string st_pattern_optional::compose () const{
        return rand() % 2 == 0 ? subpattern->compose() : "";
    }
    std::string st_pattern_function::compose () const{
        return parseExpression(frag);
    }
    std::string st_pattern_multiple::compose () const{
        return options[rand() % options.size()]->compose();
    }
    std::string st_pattern_variable::compose () const{
        return local_table[frag];
    }
    std::string st_pattern_dynamic::compose () const{
        std::stringstream ss(local_table[id]);
        if(right)
            ss << right->compose();
        return ss.str();
    }
    std::string st_pattern_optional::toString () const{
        std::stringstream ss;
        ss << '[' << subpattern->toString() << ']';
        return ss.str();
    }
    std::string st_pattern_composed::toString () const{
        return left->toString() + right->toString();
    }
    std::string st_pattern_plain::toString () const{
        return frag;
    }
    std::string st_pattern_function::toString () const{
        std::stringstream ss;
        ss << "{" << frag << "}";
        return ss.str();
    }
    std::string st_pattern_multiple::toString () const{
        std::stringstream ss;
        ss << '(' << options[0]->toString();
        for(int i = 1; i < options.size(); i++){
            ss << '|' << options[i]->toString();
        }
        ss << ')';
        return ss.str();
    }
    std::string st_pattern_variable::toString () const{
        return "$"+frag;
    }
    std::string st_pattern_dynamic::toString () const{
        std::stringstream ss;
        ss << '>' << id;
        if(right){
            ss << right->toString();
        }
        return ss.str();
    }
    std::forward_list<std::string> allCompositions(pattern){
        //TODO
    }
    void addLocalChanges(){
        for(auto ch: local_table){
            changes_table[ch.first] = ch.second;
        }
        local_table.clear();
    }
    void commitChanges(){
        for(auto ch: changes_table){
            symbol_table[ch.first] = ch.second;
        }
        changes_table.clear();
    }
    void discardLocalChanges(){
        local_table.clear();
    }
}