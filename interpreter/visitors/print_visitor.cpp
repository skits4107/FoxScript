#include "print_visitor.h"
#include <iostream>



void PrintVisitor::visit(ProgramNode& node) {
    std::cout << spaces << "Program{" << std::endl;
    spaces += " ";
    for (const auto& statement : node.statements) {
        statement->accept(*this);
    }
    spaces.pop_back();
    std::cout << spaces << "}" << std::endl;
}

void PrintVisitor::visit(IntLiteralNode& node) {
    std::cout << spaces << "Int literal{" << std::endl;
    std::cout << spaces << " " << node.val << std::endl;
    std::cout << spaces << "}" << std::endl;
}

void PrintVisitor::visit(FloatLiteralNode& node) {
    std::cout << spaces << "Float literal{" << std::endl;
    std::cout << spaces << " " << node.val << std::endl;
    std::cout << spaces << "}" << std::endl;
}

void PrintVisitor::visit(DoubleLiteralNode& node) {
    std::cout << spaces << "Double literal{" << std::endl;
    std::cout << spaces << " " << node.val << std::endl;
    std::cout << spaces << "}" << std::endl;
}

void PrintVisitor::visit(CharLiteralNode& node) {
    std::cout << spaces << "Char literal{" << std::endl;
    std::cout << spaces << " " << node.val << std::endl;
    std::cout << spaces << "}" << std::endl;
}

void PrintVisitor::visit(StringLiteralNode& node) {
    std::cout << spaces << "String literal{" << std::endl;
    std::cout << spaces << " " << node.val << std::endl;
    std::cout << spaces << "}" << std::endl;
}

void PrintVisitor::visit(BoolLiteralNode& node) {
    std::cout << spaces << "Bool literal{" << std::endl;
    std::cout << spaces << " " << node.val << std::endl;
    std::cout << spaces << "}" << std::endl;
}

void PrintVisitor::visit(ParamterNode& node) {
    std::cout << spaces << "Param node{" << std::endl;
    std::cout << spaces << " node dim: " << node.dim << std::endl;
    std::cout << spaces << " node type: " << node.type << std::endl;
    std::cout << spaces << " node identifier: " << node.identifer << std::endl;
    std::cout << spaces << "}" << std::endl;
}

void PrintVisitor::visit(CodeBlockNode& node) {
    std::cout << spaces << "Code block node{" << std::endl;
    spaces += " ";
    for (const auto& statement : node.statements) {
        statement->accept(*this);
    }
    spaces.pop_back();
    std::cout << spaces << "}" << std::endl;
}

void PrintVisitor::visit(ExpressionNode& node) {
    std::cout << spaces << "Expression node{" << std::endl;
    std::cout << spaces << " node operation: " << node.operation << std::endl;
    spaces += " ";
    node.operand1->accept(*this);
    node.operand2->accept(*this);
    spaces.pop_back();
    std::cout << spaces << "}" << std::endl;
}

void PrintVisitor::visit(TypeCastNode& node) {
    std::cout << spaces << "Type cast node{" << std::endl;
    std::cout << spaces << " type: " << node.type << std::endl;
    spaces += " ";
    node.expression->accept(*this);
    spaces.pop_back();
    std::cout << spaces << "}" << std::endl;
}

void PrintVisitor::visit(LogicalNotNode& node) {
    std::cout << spaces << "Logical not node{" << std::endl;
    spaces += " ";
    node.operand1->accept(*this);
    spaces.pop_back();
    std::cout << spaces << "}" << std::endl;
}

void PrintVisitor::visit(AssignmentStatementNode& node) {
    std::cout << spaces << "Assignment node{" << std::endl;
    std::cout << spaces << " node operation: " << node.operation << std::endl;
    std::cout << spaces << " node identifier: " << node.identifer << std::endl;
    std::cout << spaces << " node type: " << node.type << std::endl;
    spaces += " ";
    node.expression->accept(*this);
    spaces.pop_back();
    std::cout << spaces << "}" << std::endl;
}

void PrintVisitor::visit(FuncCallStatementNode& node) {
    std::cout << spaces << "FuncCall node{" << std::endl;
    std::cout << spaces << " node identifier: " << node.identifier << std::endl;
    spaces += " ";
    for (const auto& arg : node.args) {
        arg->accept(*this);
    }
    spaces.pop_back();
    std::cout << spaces << "}" << std::endl;
}

void PrintVisitor::visit(ConditionStatementNode& node) {
    std::cout << spaces << "Conditional node{" << std::endl;
    spaces += " ";
    node.expression->accept(*this);
    node.block->accept(*this);
    if (node.elseBlock != nullptr) {
        node.elseBlock->accept(*this);
    }
    spaces.pop_back();
    std::cout << spaces << "}" << std::endl;
}

void PrintVisitor::visit(ForLoopNode& node) {
    std::cout << spaces << "For loop node{" << std::endl;
    spaces += " ";
    node.assignSatement->accept(*this);
    node.condition->accept(*this);
    node.block->accept(*this);
    spaces.pop_back();
    std::cout << spaces << "}" << std::endl;
}

void PrintVisitor::visit(WhileLoopNode& node) {
    std::cout << spaces << "While loop node{" << std::endl;
    spaces += " "; 
    node.expresion->accept(*this);
    node.block->accept(*this);
    spaces.pop_back();
    std::cout << spaces << "}" << std::endl;
}

void PrintVisitor::visit(ReturnStatementNode& node) {
    std::cout << spaces << "Return statement node{" << std::endl;
    if (node.expression != nullptr){
        spaces += " "; 
        node.expression->accept(*this);
        spaces.pop_back();
    }
    std::cout << spaces << "}" << std::endl;
}

void PrintVisitor::visit(BreakStatementNode& node) {
    std::cout << spaces << "Break statement node{" << std::endl; 
    if (node.expression != nullptr){
        spaces += " "; 
        node.expression->accept(*this);
        spaces.pop_back();
    }
    std::cout << spaces << "}" << std::endl;
}

void PrintVisitor::visit(FuncDecNode& node) {
    std::cout << spaces << "FuncDeclaration node{" << std::endl;
    std::cout << spaces << " node identifier: " << node.identifier << std::endl;
    std::cout << spaces << " node type: " << node.type << std::endl;
    spaces += " ";
    for (const auto& param : node.params) {
        param->accept(*this);
    }
    node.body->accept(*this);
    spaces.pop_back();
    std::cout << spaces << "}" << std::endl;
}

void PrintVisitor::visit(ContinueStatementNode& node) {
   std::cout << spaces << "Continue statement node{}" << std::endl;
}

void PrintVisitor::visit(ArrayIndexingNode& node) {
    std::cout << spaces << "ArrayIndexing node{" << std::endl;
    spaces += " ";
    for (const auto& index : node.indices) {
        index->accept(*this);
    }
    spaces.pop_back();
    std::cout << spaces << "}" << std::endl;
}

void PrintVisitor::visit(ArrayGetElementNode& node) {
    std::cout << spaces << "ArrayGetElement node{" << std::endl;
    std::cout << spaces << " node identifier: " << node.identifer << std::endl;
    spaces += " ";
    node.indeices->accept(*this);
    spaces.pop_back();
    std::cout << spaces << "}" << std::endl;
}

void PrintVisitor::visit(IdentifierNode& node) {
    std::cout << spaces << "Identifier node{" << std::endl;
    std::cout << spaces << " node type: " << node.identifier << std::endl;
    std::cout << spaces << "}" << std::endl;
}

void PrintVisitor::visit(IncDecStatementNode& node) {
    std::cout << spaces << "IncDec node{" << std::endl;
    std::cout << spaces << " node identifier: " << node.identifer << std::endl;
    std::cout << spaces << " operation: " << (node.operation ? "increment" : "decrement") << std::endl;
    std::cout << spaces << "}" << std::endl;
}

void PrintVisitor::visit(ArrayAssignmentNode& node) {
    std::cout << spaces << "Array Assignment node{" << std::endl;
    std::cout << spaces << " node identifier: " << node.identifer << std::endl;
    spaces+=" ";
    node.inidices->accept(*this);
    if (node.arrBlock != nullptr){
        node.arrBlock->accept(*this);
    }
    spaces.pop_back();
}

void PrintVisitor::visit(ImportStatementNode& node){
    std::cout << spaces << "Import node{" << std::endl;
    std::cout << spaces << " file directory: " << node.fileDir << std::endl;
    std::cout << spaces << "}" << std::endl;
}

void PrintVisitor::visit(ElementAssignmentNode& node) {
    std::cout << spaces << "Element Assignment node{" << std::endl;
    std::cout << spaces << " operation: " << node.operation << std::endl;
    spaces += " ";
    node.getElement->accept(*this);
    node.expression->accept(*this);
    spaces.pop_back();
}

void PrintVisitor::visit(ArrayBlockNode& node) {
    std::cout << spaces << "Array Block node{" << std::endl;
    spaces += " ";
    for (const auto& value : node.values) {
        value->accept(*this);
    }
    spaces.pop_back();
}