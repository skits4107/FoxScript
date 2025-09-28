#include "compiler_visitor.h"

Value Compiler::visit(ProgramNode& node) {
    function_scope.push_back("global");

    byte_code_consts.push_back(new CodeObject());
    func_arg_reference++;

    for (const auto& statement : node.statements) {
        statement->accept(*this);
    }
}

Value Compiler::visit(IntLiteralNode& node) {
    consts.push_back(std::shared_ptr<IntValue>(new IntValue(node.val)));

    byte_code_consts.back()->code.push_back(LOAD_CONST);
    byte_code_consts.back()->code.push_back((int8_t)consts_reference);

    consts_reference++;
}

Value Compiler::visit(FloatLiteralNode& node) {
    consts.push_back(std::shared_ptr<FloatValue>(new FloatValue(node.val)));

    byte_code_consts.back()->code.push_back(LOAD_CONST);
    byte_code_consts.back()->code.push_back((int8_t)consts_reference);

    consts_reference++;
}
Value Compiler::visit(DoubleLiteralNode& node) {
    consts.push_back(std::shared_ptr<DoubleValue>(new DoubleValue(node.val)));

    byte_code_consts.back()->code.push_back(LOAD_CONST);
    byte_code_consts.back()->code.push_back((int8_t)consts_reference);

    consts_reference++;
}
Value Compiler::visit(CharLiteralNode& node) {
    consts.push_back(std::shared_ptr<CharValue>(new CharValue(node.val)));

    byte_code_consts.back()->code.push_back(LOAD_CONST);
    byte_code_consts.back()->code.push_back((int8_t)consts_reference);

    consts_reference++;
}
Value Compiler::visit(StringLiteralNode& node) {
    consts.push_back(std::shared_ptr<StringValue>(new StringValue(node.val)));

    byte_code_consts.back()->code.push_back(LOAD_CONST);
    byte_code_consts.back()->code.push_back((int8_t)consts_reference);

    consts_reference++;
}
Value Compiler::visit(BoolLiteralNode& node) {
    consts.push_back(std::shared_ptr<BoolValue>(new BoolValue(node.val)));

    byte_code_consts.back()->code.push_back(LOAD_CONST);
    byte_code_consts.back()->code.push_back((int8_t)consts_reference);

    consts_reference++;
}
Value Compiler::visit(ParamterNode& node) {
    std::string name = function_scope.back() + node.identifer;
    IdentifierInfo info(current_scope_level, variable_arg_reference);
    variables[name] = info;

    byte_code_consts.back()->local_params.push_back(variable_arg_reference);

    variable_arg_reference++;
}

Value Compiler::visit(CodeBlockNode& node) {
    
    for (const auto& statement : node.statements) {
        statement->accept(*this);
    }

}

Value Compiler::visit(ExpressionNode& node) {
    node.operand1->accept(*this);
    node.operand2->accept(*this);

    switch (node.operation){
        case ADD:
            byte_code_consts.back()->code.push_back(BINARY_ADD);
            break;
        case SUB:
            byte_code_consts.back()->code.push_back(BINARY_SUB);
            break;
        case STAR:
            byte_code_consts.back()->code.push_back(BINARY_MUL);
            break;
        case DIV:
            byte_code_consts.back()->code.push_back(BINARY_DIV);
            break;
        //TODO: continue
    }
}

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