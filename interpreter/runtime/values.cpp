#include "values.h"
#include <cmath>

//NOTE: Some method implementations depend on compiler to check compatible types


// Base Value implementations
Value::Value() : type(NONE_VAL) {}

template<typename T, typename BinaryOp>
Value* Value::numeric_arithmetic(T v, Value* other, BinaryOp op){
    //type checker ensure types can be added but we still have to check and cast to know how to add
    switch(other->type){
        case INT_VAL:{
            IntValue* other_int = static_cast<IntValue*>(other);
            return new IntValue(op(v, other_int->val));
            break;
        }
        case FLOAT_VAL:
            {FloatValue* other_flt = static_cast<FloatValue*>(other);
            return new FloatValue(op(v, other_flt->val));
            break;}
        case DOUBLE_VAL:
            {DoubleValue* other_dbl = static_cast<DoubleValue*>(other);
            return new DoubleValue(op(v, other_dbl->val));
            break;}
        default:
            //this shouldnt happen if the type checker does its job
            throw std::runtime_error("Can't add integer with this type (this shouldnt happen)");
    }
}

template<typename T, typename BinaryOp>
Value* Value::boolean_arithmetic(T v, Value* other, BinaryOp op){
    //type checker ensure types can be added but we still have to check and cast to know how to add
    switch(other->type){
        case INT_VAL:
            {IntValue* other_int = static_cast<IntValue*>(other);
            return new BoolValue(op(v, other_int->val));
            break;}
        case FLOAT_VAL:
            {FloatValue* other_flt = static_cast<FloatValue*>(other);
            return new BoolValue(op(v, other_flt->val));
            break;}
        case DOUBLE_VAL:
            {DoubleValue* other_dbl = static_cast<DoubleValue*>(other);
            return new BoolValue(op(v, other_dbl->val));
            break;}
        default:
            //this shouldnt happen if the type checker does its job
            throw std::runtime_error("Can't add integer with this type (this shouldnt happen)");
    }
}

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
std::shared_ptr<Value> Value::get_item(Value* index) { throw std::runtime_error("Operation not supported"); }
void Value::set_item(Value* index, std::shared_ptr<Value> value) { throw std::runtime_error("Operation not supported"); }
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
    BoolValue* geq_result = static_cast<BoolValue*>(geq_op(other));
    geq_result->val = ! geq_result->val;
    return geq_result;
}
Value*  IntValue::gt_op(Value* other) {
    BoolValue* geq_result = static_cast<BoolValue*>(leq_op(other));
    geq_result->val = ! geq_result->val;
    return geq_result;
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






FloatValue::FloatValue(){
    val = 0.0;
    type = FLOAT_VAL;
}
FloatValue::FloatValue(float v){
    val = v;
    type = FLOAT_VAL;
}
Value* FloatValue::add(Value* other) {
    return numeric_arithmetic(val, other, [](auto a, auto b) { return a + b; });
}

Value* FloatValue::sub(Value* other) {
    return numeric_arithmetic(val, other, [](auto a, auto b) { return a - b; });
}
Value* FloatValue::mul(Value* other) {
    return numeric_arithmetic(val, other, [](auto a, auto b) { return a * b; });
}

Value* FloatValue::div(Value* other) {
    return numeric_arithmetic(val, other, [](auto a, auto b) { return a / b; });
}

Value* FloatValue::exp(Value* other) {
    return numeric_arithmetic(val, other, [](auto a, auto b) { return pow(a,b); });
}

Value*  FloatValue::lt_op(Value* other) {
    BoolValue* geq_result = static_cast<BoolValue*>(geq_op(other));
    geq_result->val = ! geq_result->val;
    return geq_result;
}
Value* FloatValue::gt_op(Value* other) {
    BoolValue* geq_result = static_cast<BoolValue*>(leq_op(other));
    geq_result->val = ! geq_result->val;
    return geq_result;
}
Value*  FloatValue::leq_op(Value* other) {
    return boolean_arithmetic(val, other, [](auto a, auto b){return a <= b;});
}
Value*  FloatValue::geq_op(Value* other) {
    return boolean_arithmetic(val, other, [](auto a, auto b){return a >= b;});
}

Value* FloatValue::to_str(){
    return new StringValue(std::to_string(val));
}
Value* FloatValue::to_int() {
    return new IntValue(static_cast<int>(val));
}
Value* FloatValue::to_float() {
    return this;
}
Value* FloatValue::to_double() {
    return new DoubleValue(val);
}







DoubleValue::DoubleValue(){
    val = 0.0;
    type = DOUBLE_VAL;
}
DoubleValue::DoubleValue(double v){
   val = v;
    type = DOUBLE_VAL;
}
Value* DoubleValue::add(Value* other) {
    return numeric_arithmetic(val, other, [](auto a, auto b) { return a + b; });
}

Value* DoubleValue::sub(Value* other) {
    return numeric_arithmetic(val, other, [](auto a, auto b) { return a - b; });
}
Value* DoubleValue::mul(Value* other) {
    return numeric_arithmetic(val, other, [](auto a, auto b) { return a * b; });
}

Value* DoubleValue::div(Value* other) {
    return numeric_arithmetic(val, other, [](auto a, auto b) { return a / b; });
}

Value* DoubleValue::exp(Value* other) {
    return numeric_arithmetic(val, other, [](auto a, auto b) { return pow(a,b); });
}

Value*  DoubleValue::lt_op(Value* other) {
    BoolValue* geq_result = static_cast<BoolValue*>(geq_op(other));
    geq_result->val = ! geq_result->val;
    return geq_result;
}
Value* DoubleValue::gt_op(Value* other) {
    BoolValue* leq_result = static_cast<BoolValue*>(leq_op(other));
    leq_result->val = ! leq_result->val;
    return leq_result;
}
Value*  DoubleValue::leq_op(Value* other) {
    return boolean_arithmetic(val, other, [](auto a, auto b){return a <= b;});
}
Value*  DoubleValue::geq_op(Value* other) {
    return boolean_arithmetic(val, other, [](auto a, auto b){return a >= b;});
}

Value* DoubleValue::to_str(){
    return new StringValue(std::to_string(val));
}
Value* DoubleValue::to_int() {
    return new IntValue(static_cast<int>(val));
}
Value* DoubleValue::to_float() {
    return new FloatValue(static_cast<float>(val));
}
Value* DoubleValue::to_double() {
    return this;
}







BoolValue::BoolValue(){
    val = false;
    type=BOOL_VAL;
}
BoolValue::BoolValue(bool v){
    val = v;
    type=BOOL_VAL;
}
Value* BoolValue::neq_op(Value* other) {
    BoolValue* other_int = static_cast<BoolValue*>(other);
    return new BoolValue(val != other_int->val);
}
Value* BoolValue::eq_op(Value* other) {
    BoolValue* other_int = static_cast<BoolValue*>(other);
    return new BoolValue(val == other_int->val);
}

Value* BoolValue::and_op(Value* other) {
    BoolValue* other_int = static_cast<BoolValue*>(other);
    return new BoolValue(val && other_int->val);
}
Value* BoolValue::or_op(Value* other) {
    BoolValue* other_int = static_cast<BoolValue*>(other);
    return new BoolValue(val || other_int->val);
}
Value* BoolValue::not_op() {
    return new BoolValue(!val);
}



Value* BoolValue::to_str() {
    std::string str = val ? "true" : "false";
    return new StringValue(str);
}
Value* BoolValue::to_int() {
    return new IntValue(val);
}
Value* BoolValue::to_bool() {
    return this;
}








CharValue::CharValue(){
    type = CHAR_VAL;
}
CharValue::CharValue(char v){
    val = v;
    type = CHAR_VAL;
}
//char value
Value* CharValue::add(Value* other) {
    switch(other->type){
        case STRING_VAL:
            {StringValue* other_str = static_cast<StringValue*>(other);
            return new StringValue(val + other_str->val);
            break;}
        case CHAR_VAL:
            {CharValue* other_char = static_cast<CharValue*>(other);
            return new StringValue(std::string(1, val) + other_char->val);
            break;}
        default:
            //this shouldnt happen if the type checker does its job
            throw std::runtime_error("Can't add integer with this type (this shouldnt happen)");
    }
}

Value* CharValue::neq_op(Value* other) {
    BoolValue* eq_result = static_cast<BoolValue*>(eq_op(other));
    eq_result->val = ! eq_result->val;
    return eq_result;
}
Value* CharValue::eq_op(Value* other) {
    switch(other->type){
        case STRING_VAL:
            {StringValue* other_str = static_cast<StringValue*>(other);
            return new BoolValue(std::string(1, val) == other_str->val);
            break;}
        case CHAR_VAL:
           { CharValue* other_char = static_cast<CharValue*>(other);
            return new BoolValue(val == other_char->val);
            break;}
        default:
            //this shouldnt happen if the type checker does its job
            throw std::runtime_error("Can't add integer with this type (this shouldnt happen)");
    }
}

Value* CharValue::to_str() {
    return new StringValue(std::string(1, val));
}
Value* CharValue::to_int() {
    return new IntValue(val);
}
Value* CharValue::to_char() {
    return this;
}








StringValue::StringValue(){
    val = "";
    type = STRING_VAL;
}
StringValue::StringValue(std::string v) {
    val = v;
    type = STRING_VAL;
}


Value* StringValue::add(Value* other){
    switch(other->type){
        case STRING_VAL:
            {StringValue* other_str = static_cast<StringValue*>(other);
            return new StringValue(val + other_str->val);
            break;}
        case CHAR_VAL:
            {CharValue* other_char = static_cast<CharValue*>(other);
            return new StringValue(val + std::string(1, other_char->val));
            break;}
        default:
            //this shouldnt happen if the type checker does its job
            throw std::runtime_error("Can't add integer with this type (this shouldnt happen)");
    }
}

Value* StringValue::neq_op(Value* other) {
    BoolValue* eq_result = static_cast<BoolValue*>(eq_op(other));
    eq_result->val = ! eq_result->val;
    return eq_result;
}
Value* StringValue::eq_op(Value* other) {
    switch(other->type){
        case STRING_VAL:
           { StringValue* other_str = static_cast<StringValue*>(other);
            return new BoolValue(val == other_str->val);
            break;}
        case CHAR_VAL:
           { CharValue* other_char = static_cast<CharValue*>(other);
            return new BoolValue(val == std::string(1, other_char->val));
            break;}
        default:
            //this shouldnt happen if the type checker does its job
            throw std::runtime_error("Can't add integer with this type (this shouldnt happen)");
    }
}


Value* StringValue::to_str() {
    return this;
}
Value* StringValue::to_int() {
    return new IntValue(std::stoi(val));
}
Value* StringValue::to_float() {
    return new FloatValue(std::stof(val));
}
Value* StringValue::to_double() {
     return new DoubleValue(std::stod(val));
}
Value* StringValue::to_char() {
    if (val.size() != 1){
        throw std::runtime_error("cant convert string to char");
    }
    return new CharValue(val[0]);
}







//Array value implementations
ArrValue::ArrValue(int s): size(s){
    arr = new std::shared_ptr<Value>[s];
    

    for(int i = 0; i < s; i++) {
        arr[i] = nullptr;
    }

}

ArrValue::~ArrValue(){
    delete[] arr;
}

ArrValue::ArrValue(const ArrValue& other):size(other.size){
    arr = new std::shared_ptr<Value>[size];
    for(int i = 0; i < size; i++) {
        arr[i] = other.arr[i];
    }
}

Value* ArrValue::len() {
    return new IntValue(size);
}

std::shared_ptr<Value> ArrValue::get_item(Value* index){
    //type checker ensure index is of Integer type
    IntValue* i = static_cast<IntValue*>(index); 

    return arr[i->val];
}

void ArrValue::set_item(Value* index,std::shared_ptr<Value> value){
    //type checker ensure index is of Integer type
    IntValue* i = static_cast<IntValue*>(index); 

    arr[i->val] = value;
}





 FuncDecValue::FuncDecValue(std::vector<ByteCode>& c) : code(c){
    type=FUNC_DEC_VAL;
 }
 std::vector<ByteCode>& FuncDecValue::callable(){
    return code;
 }


 NoneValue::NoneValue(){
    type = NONE_VAL;
 }