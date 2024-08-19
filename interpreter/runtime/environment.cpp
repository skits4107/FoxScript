

#include "environment.h"


//returns pointer to value and the enviroment it is defined in
ValueContext Environment::getValue(std::string name){
    Value* val = nullptr;
    if (values.find(name) != values.end() ){
        val = &values[name];
    }
    else if (parent != nullptr){
        return parent->getValue(name);
    }
    
    ValueContext context(val, shared_from_this());
    return context;
}

void Environment::setValue(std::string name, Value& val){
    values[name] = val;
}