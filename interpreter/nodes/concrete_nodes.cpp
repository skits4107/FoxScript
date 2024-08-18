#include "concrete_nodes.h"
#include "../visitors/visitor.h"

void ProgramNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void IntLiteralNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void FloatLiteralNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void DoubleLiteralNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void CharLiteralNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void StringLiteralNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void BoolLiteralNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void ParamterNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void CodeBlockNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void FuncDecNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void ExpressionNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void TypeCastNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void LogicalNotNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void AssignmentStatementNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void FuncCallStatementNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void ConditionStatementNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void ForLoopNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void WhileLoopNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void ReturnStatementNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void BreakStatementNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void ContinueStatementNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void ArrayIndexingNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void ArrayGetElementNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void IdentifierNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void ArrayAssignmentNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void IncDecStatementNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void ImportStatementNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}
 
void ElementAssignmentNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void ArrayBlockNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}
