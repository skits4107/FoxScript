#include "values.h"
#include <cmath>


// Base Value implementations
Value::Value() : type(NONE_VAL) {}

Value* Value::add(Value* other) { throw std::runtime_error("Operation not supported"); }
Value* Value::sub(Value* other) { throw std::runtime_error("Operation not supported"); }
Value* Value::mul(Value* other) { throw std::runtime_error("Operation not supported"); }
Value* Value::div(Value* other) { throw std::runtime_error("Operation not supported"); }
Value* Value::exp(Value* other) { throw std::runtime_error("Operation not supported"); }
Value* Value::mod(Value* other) { throw std::runtime_error("Operation not supported"); }
Value* Value::len() { throw std::runtime_error("Operation not supported"); }
Value* Value::and_op(Value* other) { throw std::runtime_error("Operation not supported"); }
Value* Value::or_op(Value* other) { throw std::runtime_error("Operation not supported"); }
Value* Value::not_op() { throw std::runtime_error("Operation not supported"); }
Value* Value::neq_op(Value* other) { throw std::runtime_error("Operation not supported"); }
Value* Value::eq_op(Value* other) { throw std::runtime_error("Operation not supported"); }
Value* Value::lt_op(Value* other) { throw std::runtime_error("Operation not supported"); }
Value* Value::gt_op(Value* other) { throw std::runtime_error("Operation not supported"); }
Value* Value::leq_op(Value* other) { throw std::runtime_error("Operation not supported"); }
Value* Value::geq_op(Value* other) { throw std::runtime_error("Operation not supported"); }
Value* Value::get_item(Value* other) { throw std::runtime_error("Operation not supported"); }
Value* Value::set_item(Value* index, Value* value) { throw std::runtime_error("Operation not supported"); }
Value* Value::to_str() { throw std::runtime_error("Operation not supported"); }
Value* Value::to_int() { throw std::runtime_error("Operation not supported"); }
Value* Value::to_bool() { throw std::runtime_error("Operation not supported"); }
Value* Value::to_float() { throw std::runtime_error("Operation not supported"); }
Value* Value::to_char() { throw std::runtime_error("Operation not supported"); }
Value* Value::to_double() { throw std::runtime_error("Operation not supported"); }





// IntValue implementations
IntValue::IntValue() : val(0) {
    type = INT_VAL;
}

IntValue::IntValue(int v) : val(v) {
    type = INT_VAL;
}

Value* IntValue::add(Value* other) {
    return numeric_arithmetic(val, other, [](auto a, auto b) { return a + b; });
}

Value* IntValue::sub(Value* other) {
    return numeric_arithmetic(val, other, [](auto a, auto b) { return a - b; });
}
Value* IntValue::mul(Value* other) {
    return numeric_arithmetic(val, other, [](auto a, auto b) { return a * b; });
}

Value* IntValue::div(Value* other) {
    return numeric_arithmetic(val, other, [](auto a, auto b) { return a / b; });
}

Value* IntValue::exp(Value* other) {
    return numeric_arithmetic(val, other, [](auto a, auto b) { return pow(a,b); });
}

Value* IntValue::mod(Value* other) {
    //type ensured by type checker stage.
    IntValue* other_int = static_cast<IntValue*>(other);
    return new IntValue(val % other_int->val);
    
}

Value*  IntValue::neq_op(Value* other) {
    //type ensured by type checker stage.
    IntValue* other_int = static_cast<IntValue*>(other);
    return new BoolValue(val != other_int->val);
}
Value*  IntValue::eq_op(Value* other) {
    //type ensured by type checker stage.
    IntValue* other_int = static_cast<IntValue*>(other);
    return new BoolValue(val == other_int->val);

}
Value*  IntValue::lt_op(Value* other) {
    Value* leq_result = geq_op(other);
    Value* final_result = leq_result->not_op();
    delete leq_result;
    return final_result;
}
Value*  IntValue::gt_op(Value* other) {
    Value* leq_result = leq_op(other);
    Value* final_result = leq_result->not_op();
    delete leq_result;
    return final_result;
}
Value*  IntValue::leq_op(Value* other) {
    return boolean_arithmetic(val, other, [](auto a, auto b){return a <= b;});
}
Value*  IntValue::geq_op(Value* other) {
    return boolean_arithmetic(val, other, [](auto a, auto b){return a >= b;});
}

Value* IntValue::to_str(){
    return new StringValue(std::to_string(val));
}
Value* IntValue::to_int() {
    return this;
}
Value* IntValue::to_bool() {
    return new BoolValue(val);
}
Value* IntValue::to_float() {
    return new FloatValue(val);
}
Value* IntValue::to_double() {
    return new DoubleValue(val);
}
Value* IntValue::to_char() {
    return new CharValue(val);
}






//Array value implementations
ArrValue::ArrValue(int s): size(s){
    arr = new Value*[s];
    

    for(int i = 0; i < s; i++) {
        arr[i] = nullptr;
    }

}

ArrValue::~ArrValue(){
    for(int i = 0; i < size; i++) {
        delete arr[i];  // Delete each contained object
    }
    delete[] arr;
}

ArrValue::ArrValue(const ArrValue& other):size(other.size){
    arr = new Value*[size];
    for(int i = 0; i < size; i++) {
        arr[i] = other.arr[i];
    }
}

Value* ArrValue::len() {
    return new IntValue(size);
}

Value* ArrValue::get_item(Value* index){
    //type checker ensure index is of Integer type
    IntValue* i = static_cast<IntValue*>(index); 

    return arr[i->val];
}

Value* ArrValue::set_item(Value* index, Value* value){
    //type checker ensure index is of Integer type
    IntValue* i = static_cast<IntValue*>(index); 

    arr[i->val] = value;
}
//TODO: finish other types
