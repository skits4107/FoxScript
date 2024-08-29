#include "concrete_nodes.h"
#include "../visitors/visitor.h"

//overloaded operators to compare the types of values to the types of data for example when assigning a value to a varaible
bool operator==(DataType d, ValueType t){
    if (d == INT_T && t == INT_VAL){
        return true;
    }
    if (d == DOUBLE_T && t == DOUBLE_VAL){
        return true;
    }
    if (d == FLOAT_T && t == FLOAT_VAL){
        return true;
    }
    if (d == CHAR_T && t == CHAR_VAL){
        return true;
    }
    if (d == STRING_T && t == STRING_VAL){
        return true;
    }
    if (d == BOOL_T && t == BOOL_VAL){
        return true;
    }
    if (d == VOID_T && t == NONE_VAL){
        return true;
    }
    return false;
}

bool operator!=(DataType d, ValueType t){
    return !(d==t);
}

bool operator==(ValueType t, DataType d){
    return d==t;
}

bool operator!=(ValueType t, DataType d){
    return !(d==t);
}


Value ProgramNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}

Value IntLiteralNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}

Value FloatLiteralNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}

Value DoubleLiteralNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}

Value CharLiteralNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}

Value StringLiteralNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}

Value BoolLiteralNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}

Value ParamterNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}

Value CodeBlockNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}

Value FuncDecNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}

Value ExpressionNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}

Value TypeCastNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}

Value LogicalNotNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}

Value AssignmentStatementNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}

Value FuncCallStatementNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}

Value ConditionStatementNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}

Value ForLoopNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}

Value WhileLoopNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}

Value ReturnStatementNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}

Value BreakStatementNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}

Value ContinueStatementNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}

Value ArrayIndexingNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}

Value ArrayGetElementNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}

Value IdentifierNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}

Value ArrayAssignmentNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}

Value IncDecStatementNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}

Value ImportStatementNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}
 
Value ElementAssignmentNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}

Value ArrayBlockNode::accept(Visitor& visitor) {
    return visitor.visit(*this);
}
