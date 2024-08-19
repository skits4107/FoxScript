#include "eval_visitor.h"



//TODO: implement methods
Value EvalVisitor::visit(ProgramNode& node) {

    //creates a new global enviroment if there isnt one
    if (currentEnvironment == nullptr){
        currentEnvironment = std::make_shared<Environment>();
    }

    for (const auto& statement : node.statements) {
        statement->accept(*this);
    }

    currentEnvironment->printEnviroment();

    return Value();
}

Value EvalVisitor::visit(IntLiteralNode& node) {return Value(node.val);}
Value EvalVisitor::visit(FloatLiteralNode& node) {return Value(node.val);}
Value EvalVisitor::visit(DoubleLiteralNode& node) {return Value(node.val);}
Value EvalVisitor::visit(CharLiteralNode& node) {return Value(node.val);}
Value EvalVisitor::visit(StringLiteralNode& node) {return Value(node.val);}
Value EvalVisitor::visit(BoolLiteralNode& node) {return Value(node.val);}


Value EvalVisitor::visit(ParamterNode& node) {return Value();}
Value EvalVisitor::visit(CodeBlockNode& node) {return Value();}
Value EvalVisitor::visit(ExpressionNode& node)  {return Value();}
Value EvalVisitor::visit(TypeCastNode& node)  {return Value();}
Value EvalVisitor::visit(LogicalNotNode& node)  {return Value();}
Value EvalVisitor::visit(AssignmentStatementNode& node)  {return Value();}
Value EvalVisitor::visit(FuncCallStatementNode& node)  {return Value();}
Value EvalVisitor::visit(ConditionStatementNode& node)  {return Value();}
Value EvalVisitor::visit(ForLoopNode& node)  {return Value();}
Value EvalVisitor::visit(WhileLoopNode& node)  {return Value();}
Value EvalVisitor::visit(ReturnStatementNode& node)  {return Value();}
Value EvalVisitor::visit(BreakStatementNode& node) {return Value();}

Value EvalVisitor::visit(FuncDecNode& node) {
    FuncDecNode* decPtr = &node;
    Value dec = Value(decPtr);

    if(currentEnvironment->getValue(node.identifier).value != nullptr){
        std::cerr << "Error: function redefinition: " << node.identifier;
        exit(-1); 
    }
    currentEnvironment->setValue(node.identifier, dec);

    return Value();
}

Value EvalVisitor::visit(ContinueStatementNode& node) {return Value();}
Value EvalVisitor::visit(ArrayIndexingNode& node) {return Value();}
Value EvalVisitor::visit(ArrayGetElementNode& node) {return Value();}
Value EvalVisitor::visit(IdentifierNode& node)  {return Value();}
Value EvalVisitor::visit(IncDecStatementNode& node)  {return Value();}
Value EvalVisitor::visit(ArrayAssignmentNode& node) {return Value();}
Value EvalVisitor::visit(ImportStatementNode& node) {return Value();}
Value EvalVisitor::visit(ElementAssignmentNode& node) {return Value();}
Value EvalVisitor::visit(ArrayBlockNode& node) {return Value();}