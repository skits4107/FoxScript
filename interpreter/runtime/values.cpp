#include "values.h"




template<typename T>
T Value::getValue() const {
    return std::get<T>(data);
}

template<typename T>
void Value::setValue(T data){
    this->data = std::move(data);
}

 // Special getter for FuncDecNode to avoid accidental copying of pointer
FuncDecNode* Value::getFuncDec() const {
    return std::get<FuncDecNode*>(data);
}

template<typename T>
ValueType Value::deduceType() {
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