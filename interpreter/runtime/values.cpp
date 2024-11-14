#include "values.h"


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
    if (other->type == INT_VAL) {
        IntValue* other_int = static_cast<IntValue*>(other);
        return new IntValue(val + other_int->val);
    }
    // TODO: handle float and doubles
    throw std::runtime_error("Can't add integer with this type");
}

Value* IntValue::sub(Value* other) {
    if (other->type == INT_VAL) {
        IntValue* other_int = static_cast<IntValue*>(other);
        return new IntValue(val - other_int->val);
    }
    //TOOD: handle float and doubles
    throw std::runtime_error("Can't subtract integer with this type");
}

//TODO: finish int val and other types