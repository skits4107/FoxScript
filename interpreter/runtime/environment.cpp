

#include "environment.h"

Value* Environment::getValue(std::string name){
    Value* val = nullptr;
    if (values.find(name) != values.end() ){
        *val = values[name];
    }
    if (parent != nullptr){
        val = parent->getValue(name);
    }
    return val; 
}

void Environment::setValue(std::string name, Value& val){
    values[name] = val;
}