#ifndef VISITOR_H
#define VISITOR_H

#include "../forward_declarations.h"

class Visitor{
    public:
    virtual void visit(ProgramNode& node) = 0;
    virtual void visit(IntLiteralNode& node) = 0;
    virtual void visit(FloatLiteralNode& node) = 0;
    virtual void visit(DoubleLiteralNode& node) = 0;
    virtual void visit(CharLiteralNode& node) = 0;
    virtual void visit(StringLiteralNode& node) = 0;
    virtual void visit(BoolLiteralNode& node) = 0;
    virtual void visit(ParamterNode& node) = 0;
    virtual void visit(CodeBlockNode& node) = 0;
    virtual void visit(ExpressionNode& node) = 0;
    virtual void visit(TypeCastNode& node) = 0;
    virtual void visit(LogicalNotNode& node) = 0;
    virtual void visit(AssignmentStatementNode& node) = 0;
    virtual void visit(FuncCallStatementNode& node) = 0;
    virtual void visit(ConditionStatementNode& node) = 0;
    virtual void visit(ForLoopNode& node) = 0;
    virtual void visit(WhileLoopNode& node) = 0;
    virtual void visit(ReturnStatementNode& node) = 0;
    virtual void visit(BreakStatementNode& node) = 0;
    virtual void visit(FuncDecNode& node) = 0;
    virtual void visit(ContinueStatementNode& node) = 0;
    virtual void visit(ArrayIndexingNode& node) = 0;
    virtual void visit(ArrayGetElementNode& node) = 0;
    virtual void visit(IdentifierNode& node) = 0;
    virtual void visit(IncDecStatementNode& node) = 0;
    virtual void visit(ArrayAssignmentNode& node) = 0;
    virtual void visit(ImportStatementNode& node) = 0;
    virtual void visit(ElementAssignmentNode& node) = 0;
    virtual void visit(ArrayBlockNode& node) = 0;

};

#endif