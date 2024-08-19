#ifndef VISITOR_H
#define VISITOR_H

#include "../forward_declarations.h"
#include "../runtime/values.h"

class Visitor{
    public:
    virtual Value visit(ProgramNode& node) = 0;
    virtual Value visit(IntLiteralNode& node) = 0;
    virtual Value visit(FloatLiteralNode& node) = 0;
    virtual Value visit(DoubleLiteralNode& node) = 0;
    virtual Value visit(CharLiteralNode& node) = 0;
    virtual Value visit(StringLiteralNode& node) = 0;
    virtual Value visit(BoolLiteralNode& node) = 0;
    virtual Value visit(ParamterNode& node) = 0;
    virtual Value visit(CodeBlockNode& node) = 0;
    virtual Value visit(ExpressionNode& node) = 0;
    virtual Value visit(TypeCastNode& node) = 0;
    virtual Value visit(LogicalNotNode& node) = 0;
    virtual Value visit(AssignmentStatementNode& node) = 0;
    virtual Value visit(FuncCallStatementNode& node) = 0;
    virtual Value visit(ConditionStatementNode& node) = 0;
    virtual Value visit(ForLoopNode& node) = 0;
    virtual Value visit(WhileLoopNode& node) = 0;
    virtual Value visit(ReturnStatementNode& node) = 0;
    virtual Value visit(BreakStatementNode& node) = 0;
    virtual Value visit(FuncDecNode& node) = 0;
    virtual Value visit(ContinueStatementNode& node) = 0;
    virtual Value visit(ArrayIndexingNode& node) = 0;
    virtual Value visit(ArrayGetElementNode& node) = 0;
    virtual Value visit(IdentifierNode& node) = 0;
    virtual Value visit(IncDecStatementNode& node) = 0;
    virtual Value visit(ArrayAssignmentNode& node) = 0;
    virtual Value visit(ImportStatementNode& node) = 0;
    virtual Value visit(ElementAssignmentNode& node) = 0;
    virtual Value visit(ArrayBlockNode& node) = 0;

};

#endif