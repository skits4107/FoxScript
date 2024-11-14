#ifndef VALUES_H
#define VALUES_H

#include "value_type.h"
#include <variant>
#include <string>
#include <vector>
#include "../forward_declarations.h"
#include <stdexcept>

class Value {
public:
    ValueType type;

    Value();
    virtual ~Value() = default;

    // Binary operations
    virtual Value* add(Value* other);
    virtual Value* sub(Value* other);
    virtual Value* mul(Value* other);
    virtual Value* div(Value* other);
    virtual Value* exp(Value* other);
    virtual Value* mod(Value* other);
    
    // Container operations
    virtual Value* len();
    virtual Value* get_item(Value* other);
    virtual Value* set_item(Value* index, Value* value);

    // Logical operations
    virtual Value* and_op(Value* other);
    virtual Value* or_op(Value* other);
    virtual Value* not_op();

    // Comparison operations
    virtual Value* neq_op(Value* other);
    virtual Value* eq_op(Value* other);
    virtual Value* lt_op(Value* other);
    virtual Value* gt_op(Value* other);
    virtual Value* leq_op(Value* other);
    virtual Value* geq_op(Value* other);

    // Type conversions
    virtual Value* to_str();
    virtual Value* to_int();
    virtual Value* to_bool();
    virtual Value* to_float();
    virtual Value* to_char();
    virtual Value* to_double();
};

class IntValue : public Value{
    public:
    int val;

    IntValue();
    explicit IntValue(int v);
    
    // override or possible operations for integer values
    Value* add(Value* other) override;
    Value* sub(Value* other) override;
    Value* mul(Value* other) override;
    Value* div(Value* other) override;
    Value* exp(Value* other) override;
    Value* mod(Value* other) override;

    Value* neq_op(Value* other) override;
    Value* eq_op(Value* other) override;
    Value* lt_op(Value* other) override;
    Value* gt_op(Value* other) override;
    Value* leq_op(Value* other) override;
    Value* geq_op(Value* other) override;

    Value* to_str() override;
    Value* to_int() override;
    Value* to_bool() override;
    Value* to_float() override;
    Value* to_double() override;
    Value* to_char() override;

};

#endif