#ifndef VALUES_H
#define VALUES_H

#include "value_type.cpp"
#include <variant>
#include <string>
#include <vector>
#include "../forward_declarations.h"


class Value{

   using VariantType = std::variant<
        int, double, float, std::string, char, bool,
        FuncDecNode*,
        std::vector<int>, std::vector<double>, std::vector<float>,
        std::vector<std::string>, std::vector<char>
    >;
    
    VariantType data;
    ValueType type;

    template<typename T>
    static ValueType deduceType();

    public:
    template<typename T>
    Value(T value) : data(std::move(value)), type(deduceType<T>()) {}

    Value() : data(0), type(ValueType::NONE){}

    // Special constructor for FuncDecNode pointer
    Value(FuncDecNode* funcDec) : data(funcDec), type(ValueType::FUNC_DEC) {}

    ~Value() {
        // Note: We don't delete FuncDecNode* here, as we don't own it
    }

    template<typename T>
    T getValue() const;

    template<typename T>
    void setValue(T data);

    // Special getter for FuncDecNode to avoid accidental copying of pointer
    FuncDecNode* getFuncDec() const;



};

#endif