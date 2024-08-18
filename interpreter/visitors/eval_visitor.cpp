#include "eval_visitor.h"



//TODO: implement methods after parser is done
void EvalVisitor::visit(ProgramNode& node) {}
void EvalVisitor::visit(IntLiteralNode& node) {}
void EvalVisitor::visit(FloatLiteralNode& node) {}
void EvalVisitor::visit(DoubleLiteralNode& node) {}
void EvalVisitor::visit(CharLiteralNode& node) {}
void EvalVisitor::visit(StringLiteralNode& node) {}
void EvalVisitor::visit(BoolLiteralNode& node) {}
void EvalVisitor::visit(ParamterNode& node) {}
void EvalVisitor::visit(CodeBlockNode& node) {}
void EvalVisitor::visit(ExpressionNode& node)  {}
void EvalVisitor::visit(TypeCastNode& node)  {}
void EvalVisitor::visit(LogicalNotNode& node)  {}
void EvalVisitor::visit(AssignmentStatementNode& node)  {}
void EvalVisitor::visit(FuncCallStatementNode& node)  {}
void EvalVisitor::visit(ConditionStatementNode& node)  {}
void EvalVisitor::visit(ForLoopNode& node)  {}
void EvalVisitor::visit(WhileLoopNode& node)  {}
void EvalVisitor::visit(ReturnStatementNode& node)  {}
void EvalVisitor::visit(BreakStatementNode& node) {}
void EvalVisitor::visit(FuncDecNode& node) {}
void EvalVisitor::visit(ContinueStatementNode& node) {}
void EvalVisitor::visit(ArrayIndexingNode& node) {}
void EvalVisitor::visit(ArrayGetElementNode& node) {}
void EvalVisitor::visit(IdentifierNode& node)  {}
void EvalVisitor::visit(IncDecStatementNode& node)  {}
void EvalVisitor::visit(ArrayAssignmentNode& node) {}
void EvalVisitor::visit(ImportStatementNode& node) {}