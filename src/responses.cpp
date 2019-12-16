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
    ResponseModule rootModule;
    std::vector<pattern> init;
    bool ResponseModule::respond(const std::string& str, std::ostream& out){
        bool match = false;
        for(auto r : responses){
            match = r->respond(str,out) || match;
        }
        if(!match){
            for(auto r : defaultResponses){
                match = r->respond(str,out) || match;
            }
        }
        return match;
    }
    bool SimpleResponse::respond(const std::string& str, std::ostream& out){
        st::scope();
        if( (input == nullptr || input->match(str)) && condition->evaluateBool() ){
            out << output->compose() << endl;
            st::add(st::newId());
            st::descope();
            return true;
        }else{
            st::descope();
            return false;
        }
    }
    bool RecursiveResponse::respond(const std::string& str, std::ostream& out){
        bool ret;
        st::scope();
        if( (input == nullptr || input->match(str)) && condition->evaluateBool() ){
            int id = st::newId();
            ret = responses.respond(new_answer == nullptr? str: new_answer->compose(),out);
            if(ret){
                st::add(id);
            }
        }else{
            ret = false;
        }
        st::descope();
        return ret;
    }
    ResponseModule moduleFromArray(Value& v, bool verbose){
        ResponseModule ret;
        auto r = v.GetArray();
        for(auto it = r.Begin(); it != r.End(); it++){
            myassert(it->HasMember("condition") && (*it)["condition"].IsString(), "Every response must have a \"condition\" attribute");
            pattern input;
            auto target = &ret.responses;
            if(it->HasMember("input")){
                myassert((*it)["input"].IsString(),"\"input\" attribute must be a string");
                input = parsePattern((*it)["input"].GetString(), verbose);
            }else{
                input = nullptr;
                target = &ret.defaultResponses;
            }
            if(it->HasMember("responses")){
                myassert((*it)["responses"].IsArray(), "\"responses\" attribute must be an array");
                auto res = new RecursiveResponse;
                res->input = input;
                res->condition = parseExpression((*it)["condition"].GetString(),verbose);
                if(it->HasMember("question")){
                    myassert((*it)["question"].IsString(), "\"question\" attribute must be a string");
                    res->new_answer = parsePattern((*it)["question"].GetString(),verbose);
                }else{
                    res->new_answer = nullptr;
                }
                res->responses = moduleFromArray((*it)["responses"], verbose);
                target->push_back(response(res));
            }else{
                myassert(it->HasMember("output"),"Every response must have a \"output\" or \"responses\" attribute");
                myassert((*it)["output"].IsString(),"\"output\" attribute must be a string");
                auto res = new SimpleResponse;
                res->input = input;
                res->condition = parseExpression((*it)["condition"].GetString(), verbose);
                res->output = parsePattern((*it)["output"].GetString(), verbose);
                target->push_back(response(res));
            }
        }
        return ret;
    }
    void loadSpecs(const std::string& filename, bool verbose){
        try{
            Document d;
            /*ifstream fin(filename.c_str());
            IStreamWrapper isw(fin);
            d.ParseStream(isw);
            fin.close();*/
            std::string json = preprocesJSONFile(filename);
            StringStream s(json.c_str());
            ParseResult info = d.ParseStream(s);
            if(info.IsError()){
                std::stringstream errinfo;
                errinfo << json.substr(info.Offset(),10) << endl << rapidjson::GetParseError_En(info.Code()); 
                throw std::runtime_error(errinfo.str().c_str());
            }
            myassert(d.IsObject(),"Expected object as main structure");
            myassert(d.HasMember("init") && d["init"].IsString(), "Expected main attribute \"init\" to be a string");
            myassert(d.HasMember("responses") && d["responses"].IsArray(), "Expected main attribute \"responses\" to be an array");
            
            init.push_back(parsePattern(d["init"].GetString(), verbose));
            
            rootModule = moduleFromArray(d["responses"], verbose);
            
        }catch(std::exception& e){
            #ifdef DEBUG
            cerr << "\e[38;2;250;0;0m" << e.what() << "\e[0m" << endl;
            #else
            cerr << "Error loading JSON file " << filename << endl;
            #endif
            throw std::runtime_error(e.what());
        }
    }
    std::string respond(const std::string& str){
        std::stringstream ret;
        rootModule.respond(str,ret);
        st::commit(); // we add to the global table the changes saved during the response-
        return ret.str();
    }
    void launch(){
        st::scope();
        st::set("_TA_RUNNING_","1");
        for(auto p : init){
            cout << p->compose ();
        }
        st::add(0);
        st::descope();
        st::commit();
        
        auto finish = parseExpression("!@_TA_RUNNING_");
        
        while( !finish->evaluateBool() && !cin.eof()){
            try{
                string str;
                cout << ">";
                getline(cin,str);
                cout << respond(str);
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
