#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H


#include <unordered_map>
#include "values.h"
#include <memory>
#include <iostream>


class Environment{

    std::unordered_map<std::string, Value> values;

    std::shared_ptr<Environment> parent;
    std::shared_ptr<Environment> caller;

    public:

    Environment(std::shared_ptr<Environment> p=nullptr, std::shared_ptr<Environment> c=nullptr) : parent(p), caller(c){}

    Value* getValue(std::string name);

    void setValue(std::string name, Value& val);

};


#endif