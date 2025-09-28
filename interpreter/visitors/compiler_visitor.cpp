#include "compiler_visitor.h"

Value Compiler::visit(ProgramNode& node) {

}

Value Compiler::visit(IntLiteralNode& node) {

}

Value Compiler::visit(FloatLiteralNode& node) {

}
Value Compiler::visit(DoubleLiteralNode& node) {}
Value Compiler::visit(CharLiteralNode& node) {}
Value Compiler::visit(StringLiteralNode& node) {}
Value Compiler::visit(BoolLiteralNode& node) {}
Value Compiler::visit(ParamterNode& node) {}

Value Compiler::visit(CodeBlockNode& node) {}

Value Compiler::visit(ExpressionNode& node) {}

Value Compiler::visit(TypeCastNode& node) {}
Value Compiler::visit(LogicalNotNode& node) {}
Value Compiler::visit(AssignmentStatementNode& node) {}
Value Compiler::visit(FuncCallStatementNode& node) {}
Value Compiler::visit(ConditionStatementNode& node) {}
Value Compiler::visit(ForLoopNode& node) {}
Value Compiler::visit(WhileLoopNode& node) {}
Value Compiler::visit(ReturnStatementNode& node) {}
Value Compiler::visit(BreakStatementNode& node) {}
Value Compiler::visit(FuncDecNode& node) {}
Value Compiler::visit(ContinueStatementNode& node) {}
Value Compiler::visit(ArrayIndexingNode& node) {}
Value Compiler::visit(ArrayGetElementNode& node) {}
Value Compiler::visit(IdentifierNode& node) {}
Value Compiler::visit(IncDecStatementNode& node) {}
Value Compiler::visit(ArrayAssignmentNode& node) {}
Value Compiler::visit(ImportStatementNode& node) {}
Value Compiler::visit(ElementAssignmentNode& node) {}
Value Compiler::visit(ArrayBlockNode& node){}