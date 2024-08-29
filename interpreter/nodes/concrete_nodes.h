#ifndef CONCRETE_NODES_H
#define CONCRETE_NODES_H

#include "node.h"
#include <iostream>
#include <vector>
#include <memory>
#include "../tokens/token_type.h"
#include "../runtime/value_type.h"


enum DataType {INT_T, DOUBLE_T, FLOAT_T, CHAR_T, STRING_T, BOOL_T, VOID_T, INVALID_TYPE};

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


class ProgramNode : public Node{
    public:
    std::vector<std::unique_ptr<Node>> statements;

    Value accept(Visitor& visitor) override;
};

class IntLiteralNode : public Node{
    public:
    int val;
    Value accept(Visitor& visitor) override;
};

class FloatLiteralNode : public Node{
    public:
    float val;
    Value accept(Visitor& visitor) override;
};

class DoubleLiteralNode : public Node{
    public:
    double val;
   Value accept(Visitor& visitor) override;
};

class CharLiteralNode : public Node{
    public:
    char val;
    Value accept(Visitor& visitor) override;
};

class StringLiteralNode : public Node{
    public:
    std::string val;
    Value accept(Visitor& visitor) override;
};

class BoolLiteralNode : public Node{
    public:
    bool val;
    Value accept(Visitor& visitor) override;
};

class ParamterNode : public Node{
    public:
    DataType type;
    std::string identifer;
    int dim;
    Value accept(Visitor& visitor) override;
};

class CodeBlockNode : public Node{
    public:
    std::vector<std::unique_ptr<Node>> statements;
    Value accept(Visitor& visitor) override;
};

class FuncDecNode : public Node{
    public:
    DataType type;
    std::vector<std::unique_ptr<ParamterNode>> params; 
    std::unique_ptr<CodeBlockNode> body;
    std::string identifier;
    Value accept(Visitor& visitor) override;
};

//something with a relational or airthmetic operators
class ExpressionNode : public Node{
    public:
    std::unique_ptr<Node> operand1;
    std::unique_ptr<Node> operand2;
    TokenType operation;
   Value accept(Visitor& visitor) override;
};

class TypeCastNode : public Node{
    public:
        DataType type;
        std::unique_ptr<Node> expression;
    Value accept(Visitor& visitor) override ;
};


class LogicalNotNode : public Node{ //a logicalTerm that negates. otherwise the logical term is really another node
    public:
    std::unique_ptr<Node> operand1;
    Value accept(Visitor& visitor) override;
};

class AssignmentStatementNode : public Node{
    public:
    DataType type;
    std::string identifer;
    TokenType operation;
    std::unique_ptr<Node> expression;
    Value accept(Visitor& visitor) override;
};

class FuncCallStatementNode : public Node{
    public:
    std::string identifier;
    std::vector<std::unique_ptr<Node>> args;
    Value accept(Visitor& visitor) override;
};

class ConditionStatementNode : public Node{ //can be used for elif as well
    public:
    std::unique_ptr<Node> expression;
    std::unique_ptr<CodeBlockNode> block;
    std::unique_ptr<Node> elseBlock; //may also be another condition node as it can represent an elif as well
    Value accept(Visitor& visitor) override;

};

class ForLoopNode : public Node{
    public:
    std::unique_ptr<Node> assignSatement;
    std::unique_ptr<Node> condition;
    std::unique_ptr<Node> increment;
    std::unique_ptr<CodeBlockNode> block;
    Value accept(Visitor& visitor) override;
};

class WhileLoopNode : public Node{
    public:
    std::unique_ptr<Node> expresion;
    std::unique_ptr<CodeBlockNode> block;
    Value accept(Visitor& visitor) override;
};

class ReturnStatementNode : public Node{
    public:
    std::unique_ptr<Node> expression; //what to return
    Value accept(Visitor& visitor) override;
};

class BreakStatementNode : public Node{
    public:
    std::unique_ptr<Node> expression; //how many loops to break out of
    Value accept(Visitor& visitor) override;
};

class ContinueStatementNode : public Node{
    public:
    Value accept(Visitor& visitor) override;
};

class ArrayIndexingNode : public Node{
    public:
    std::vector<std::unique_ptr<Node>> indices;
    Value accept(Visitor& visitor) override;
};

class ArrayGetElementNode : public Node{
    public:
    std::unique_ptr<ArrayIndexingNode> indeices;
    std::string identifer;
    Value accept(Visitor& visitor) override;
};


//used when there is an identifier but isnt for another node (like an assignment node or func declaration or func call node)
//such as when you use a variable inside an expression or function call paramter
class IdentifierNode : public Node{
    public:
    std::string identifier;
    Value accept(Visitor& visitor) override;
};


class ArrayAssignmentNode : public Node{
    public:
    std::unique_ptr<ArrayIndexingNode> inidices;
    std::unique_ptr<ArrayBlockNode> arrBlock;
    std::string identifer;
    Value accept(Visitor& visitor) override;
};

class IncDecStatementNode : public Node{
    public:
    std::string identifer;
    bool operation; //true for inc and false for neg
    Value accept(Visitor& visitor) override;
};


//since string is only thing it might have it doesnt contain any node, just a direct string
class ImportStatementNode : public Node{
    public:
     std::string fileDir;
     Value accept(Visitor& visitor) override;
};

class ElementAssignmentNode : public Node{
    public:
     std::unique_ptr<ArrayGetElementNode> getElement;
     TokenType operation;
     std::unique_ptr<Node> expression;
     Value accept(Visitor& visitor) override;
};
class ArrayBlockNode : public Node{
    public:
    std::vector<std::unique_ptr<Node>> values;
    Value accept(Visitor& visitor) override;
};

#endif