#ifndef VALUES_H
#define VALUES_H

#include "value_type.h"
#include <variant>
#include <string>
#include <vector>
#include "../forward_declarations.h"
#include <stdexcept>

//forward class declarations (for use in the casting functions of base value class)
class IntValue;
class DoubleValue;
class FloatValue;
class CharValue;
class BoolValue;
class StringValue;
class FuncDecValue;
class ArrValue;

class Value {
private:

protected:

    //functions for numeric types to use to maximize code reuse.
    template<typename T, typename BinaryOp>
    static Value* numeric_arithmetic(T v, Value* other, BinaryOp op);
    template<typename T, typename BinaryOp>
    static Value* boolean_arithmetic(T v, Value* other, BinaryOp op);
    
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
    virtual Value* get_item(Value* index);
    virtual void set_item(Value* index, Value* value);

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

    //function stuff
    virtual Value* callable();


};

class IntValue : public Value{
    public:
    int val;

    IntValue();
    IntValue(int v);
    
    // override all possible operations for integer values
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

class FloatValue : public Value{
    public:
    float val;

    FloatValue();
    FloatValue(float v);
    
    // override all possible operations for float values
    Value* add(Value* other) override;
    Value* sub(Value* other) override;
    Value* mul(Value* other) override;
    Value* div(Value* other) override;
    Value* exp(Value* other) override;

    Value* lt_op(Value* other) override;
    Value* gt_op(Value* other) override;
    Value* leq_op(Value* other) override;
    Value* geq_op(Value* other) override;

    Value* to_str() override;
    Value* to_int() override;
    Value* to_float() override;
    Value* to_double() override;

};

class DoubleValue : public Value{
    public:
    double val;

    DoubleValue();
    DoubleValue(double v);
    
    // override all possible operations for double values
    Value* add(Value* other) override;
    Value* sub(Value* other) override;
    Value* mul(Value* other) override;
    Value* div(Value* other) override;
    Value* exp(Value* other) override;

    Value* lt_op(Value* other) override;
    Value* gt_op(Value* other) override;
    Value* leq_op(Value* other) override;
    Value* geq_op(Value* other) override;

    Value* to_str() override;
    Value* to_int() override;
    Value* to_float() override;
    Value* to_double() override;

};

class BoolValue : public Value{
    public:
    bool val;

    BoolValue();
    BoolValue(bool v);
    
    // override all possible operations for bool values

    Value* neq_op(Value* other) override;
    Value* eq_op(Value* other) override;

    Value* and_op(Value* other) override;
    Value* or_op(Value* other) override;
    Value* not_op() override;



    Value* to_str() override;
    Value* to_int() override;
    Value* to_bool() override;

};

class CharValue : public Value{
    public:
    char val;

    CharValue();
    CharValue(char v);
    
    // override all possible operations for char values
    Value* add(Value* other) override;


    Value* neq_op(Value* other) override;
    Value* eq_op(Value* other) override;
  

    Value* to_str() override;
    Value* to_int() override;
    Value* to_char() override;

};

class StringValue : public Value{
    public:
    std::string val;

    StringValue();
    StringValue(std::string v);

    Value* add(Value* other) override;

    Value* neq_op(Value* other) override;
    Value* eq_op(Value* other) override;
  

    Value* to_str() override;
    Value* to_int() override;;
    Value* to_float() override;
    Value* to_double() override;
    Value* to_char() override;
};


class ArrValue : public Value{
    Value** arr;

    public:
    const int size;

    ArrValue(int s);

    ~ArrValue();

    ArrValue(const ArrValue& other);

    Value* len() override;
    Value* get_item(Value* index) override;
    void set_item(Value* index, Value* value) override;

};

//TODO: come back and finish function value
class FuncDecValue : public Value{
    public:

    FuncDecValue();

    Value* callable() override;

};

class NoneValue : public Value{
    public:
    NoneValue();
};
#endif