#ifndef VALUES_H
#define VALUES_H

#include "value_type.h"
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
    ValueType deduceType() {
        if constexpr (std::is_same_v<T, int>) return ValueType::INT_VAL;
        else if constexpr (std::is_same_v<T, double>) return ValueType::DOUBLE_VAL;
        else if constexpr (std::is_same_v<T, float>) return ValueType::FLOAT_VAL;
        else if constexpr (std::is_same_v<T, std::string>) return ValueType::STRING_VAL;
        else if constexpr (std::is_same_v<T, char>) return ValueType::CHAR_VAL;
        else if constexpr (std::is_same_v<T, bool>) return ValueType::BOOL_VAL;
        else if constexpr (std::is_same_v<T, FuncDecNode*>) return ValueType::FUNC_DEC_VAL;
        else if constexpr (std::is_same_v<T, std::vector<int>>) return ValueType::INT_ARR_VAL;
        else if constexpr (std::is_same_v<T, std::vector<double>>) return ValueType::DOUBLE_ARR_VAL;
        else if constexpr (std::is_same_v<T, std::vector<float>>) return ValueType::FLOAT_ARR_VAL;
        else if constexpr (std::is_same_v<T, std::vector<std::string>>) return ValueType::STRING_ARR_VAL;
        else if constexpr (std::is_same_v<T, std::vector<char>>) return ValueType::CHAR_ARR_VAL;
        else return ValueType::NONE_VAL;
    }

    public:
    template<typename T>
    Value(T value) : data(std::move(value)), type(deduceType<T>()) {}

    Value() : data(0), type(ValueType::NONE_VAL){}

    // Special constructor for FuncDecNode pointer
    Value(FuncDecNode* funcDec) : data(funcDec), type(ValueType::FUNC_DEC_VAL) {}

    ~Value() {
        // Note: We don't delete FuncDecNode* here, as we don't own it
    }

    template<typename T>
    T getValue() const {
        return std::get<T>(data);
    }

    template<typename T>
    void setValue(T data){
        this->data = std::move(data);
    }

    // Special getter for FuncDecNode to avoid accidental copying of pointer
    FuncDecNode* getFuncDec() const;



};

#endif