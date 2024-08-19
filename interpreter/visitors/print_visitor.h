#ifndef PRINT_VISITOR_H
#define PRINT_VISITOR_H

#include "visitor.h"
#include "../nodes/concrete_nodes.h"

class PrintVisitor : public Visitor{
    std::string spaces = "";
    public:
     Value visit(ProgramNode& node) override;

     Value visit(IntLiteralNode& node) override;

     Value visit(FloatLiteralNode& node) override;
     Value visit(DoubleLiteralNode& node) override;
     Value visit(CharLiteralNode& node) override;
     Value visit(StringLiteralNode& node) override;
     Value visit(BoolLiteralNode& node) override;
     Value visit(ParamterNode& node) override;

     Value visit(CodeBlockNode& node) override;

     Value visit(ExpressionNode& node) override;

     Value visit(TypeCastNode& node) override;
     Value visit(LogicalNotNode& node) override;
     Value visit(AssignmentStatementNode& node) override;
     Value visit(FuncCallStatementNode& node) override;
     Value visit(ConditionStatementNode& node) override;
     Value visit(ForLoopNode& node) override;
     Value visit(WhileLoopNode& node) override;
     Value visit(ReturnStatementNode& node) override;
     Value visit(BreakStatementNode& node) override;
     Value visit(FuncDecNode& node) override;
     Value visit(ContinueStatementNode& node) override;
     Value visit(ArrayIndexingNode& node) override;
     Value visit(ArrayGetElementNode& node) override;
     Value visit(IdentifierNode& node) override;
     Value visit(IncDecStatementNode& node) override;
     Value visit(ArrayAssignmentNode& node) override;
     Value visit(ImportStatementNode& node) override;
     Value visit(ElementAssignmentNode& node) override;
     Value visit(ArrayBlockNode& node) override;

};

#endif