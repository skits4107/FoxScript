#ifndef EVAL_VISITOR_H
#define EVAL_VISITOR_H

#include "visitor.h"
#include "../nodes/concrete_nodes.h"

class EvalVisitor : public Visitor{
    public:
     void visit(ProgramNode& node) override;
     void visit(IntLiteralNode& node) override;
     void visit(FloatLiteralNode& node) override;
     void visit(DoubleLiteralNode& node) override;
     void visit(CharLiteralNode& node) override;
     void visit(StringLiteralNode& node) override;
     void visit(BoolLiteralNode& node) override;
     void visit(ParamterNode& node) override;
     void visit(CodeBlockNode& node) override;
     void visit(ExpressionNode& node) override ;
     void visit(TypeCastNode& node) override ;
     void visit(LogicalNotNode& node) override ;
     void visit(AssignmentStatementNode& node) override ;
     void visit(FuncCallStatementNode& node) override ;
     void visit(ConditionStatementNode& node) override ;
     void visit(ForLoopNode& node) override ;
     void visit(WhileLoopNode& node) override ;
     void visit(ReturnStatementNode& node) override ;
     void visit(BreakStatementNode& node) override;
     void visit(FuncDecNode& node) override ;
     void visit(ContinueStatementNode& node) override ;
     void visit(ArrayIndexingNode& node) override ;
     void visit(ArrayGetElementNode& node) override ;
     void visit(IdentifierNode& node) override ;
     void visit(IncDecStatementNode& node) override ;
     void visit(ArrayAssignmentNode& node) override ;
     void visit(ImportStatementNode& node) override;
};

#endif