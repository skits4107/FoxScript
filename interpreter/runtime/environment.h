#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H


#include <unordered_map>
#include "values.h"
#include <memory>
#include <iostream>


class Environment;
struct ValueContext {
    Value* value;
    std::shared_ptr<Environment> definingEnv;

    ValueContext(Value* v = nullptr, std::shared_ptr<Environment> env = nullptr)
        : value(v), definingEnv(env) {}
};


class Environment : public std::enable_shared_from_this<Environment>{

    std::unordered_map<std::string, Value> values;

    public:

    std::shared_ptr<Environment> parent;
    std::shared_ptr<Environment> caller;

    Environment(std::shared_ptr<Environment> p=nullptr, std::shared_ptr<Environment> c=nullptr) : parent(p), caller(c){}

    ValueContext getValue(std::string name);

    void setValue(std::string name, Value& val);

    void printEnviroment();

};


#endif