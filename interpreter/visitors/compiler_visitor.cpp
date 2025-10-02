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
    current_type = INT_T;
}

Value Compiler::visit(FloatLiteralNode& node) {
    consts.push_back(std::shared_ptr<FloatValue>(new FloatValue(node.val)));

    byte_code_consts.back()->code.push_back(LOAD_CONST);
    byte_code_consts.back()->code.push_back((int8_t)consts_reference);

    consts_reference++;
    current_type = FLOAT_T;
}
Value Compiler::visit(DoubleLiteralNode& node) {
    consts.push_back(std::shared_ptr<DoubleValue>(new DoubleValue(node.val)));

    byte_code_consts.back()->code.push_back(LOAD_CONST);
    byte_code_consts.back()->code.push_back((int8_t)consts_reference);

    consts_reference++;
    current_type = DOUBLE_T;
}
Value Compiler::visit(CharLiteralNode& node) {
    consts.push_back(std::shared_ptr<CharValue>(new CharValue(node.val)));

    byte_code_consts.back()->code.push_back(LOAD_CONST);
    byte_code_consts.back()->code.push_back((int8_t)consts_reference);

    consts_reference++;
    current_type = CHAR_T;
}
Value Compiler::visit(StringLiteralNode& node) {
    consts.push_back(std::shared_ptr<StringValue>(new StringValue(node.val)));

    byte_code_consts.back()->code.push_back(LOAD_CONST);
    byte_code_consts.back()->code.push_back((int8_t)consts_reference);

    consts_reference++;
    current_type = STRING_T;
}
Value Compiler::visit(BoolLiteralNode& node) {
    consts.push_back(std::shared_ptr<BoolValue>(new BoolValue(node.val)));

    byte_code_consts.back()->code.push_back(LOAD_CONST);
    byte_code_consts.back()->code.push_back((int8_t)consts_reference);

    consts_reference++;
    current_type = BOOL_T;
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
        case EXP:
            byte_code_consts.back()->code.push_back(BINARY_EXP);
            break;
        case AND:
             byte_code_consts.back()->code.push_back(AND_LOGIC);
            break;
        case OR:
             byte_code_consts.back()->code.push_back(OR_LOGIC);
            break;
        case EQ:
            byte_code_consts.back()->code.push_back(EQUAL);
            break;
        case NEQ:
            byte_code_consts.back()->code.push_back(NOT_EQUAL);
            break;
        case LT:
            byte_code_consts.back()->code.push_back(LESS_THAN);
            break;
        case LEQ:
            byte_code_consts.back()->code.push_back(LESS_THAN_EQUAL);
            break;
        case GT:
            byte_code_consts.back()->code.push_back(GREATER_THAN);
            break;
        case GEQ:
            byte_code_consts.back()->code.push_back(GREATER_THAN_EQUAL);
            break;
        case MOD:
            byte_code_consts.back()->code.push_back(BINARY_MOD);
            break;
        default:
            break;
    }
}

Value Compiler::visit(TypeCastNode& node) {
    node.expression->accept(*this);

    switch (node.type)
    {
    case STRING_T:
        byte_code_consts.back()->code.push_back(TO_STR);
        break;
    case INT_T:
        byte_code_consts.back()->code.push_back(TO_INT);
        break;
    case DOUBLE_T:
        if (current_type == BOOL_T){compileError("cant convert bool to double");}
        if (current_type == CHAR_T){compileError("cant convert char to double");}
        byte_code_consts.back()->code.push_back(TO_DOUBLE);
        break;
    case FLOAT_T:
        if (current_type == BOOL_T){compileError("cant convert bool to float");}
        if (current_type == CHAR_T){compileError("cant convert char to float");}
        byte_code_consts.back()->code.push_back(TO_FLOAT);
        break;
    case CHAR_T:
        if (current_type == BOOL_T){compileError("cant convert bool to char");}
        if (current_type == DOUBLE_T){compileError("cant convert double to char");}
        if (current_type == FLOAT_T){compileError("cant convert float to char");}
        byte_code_consts.back()->code.push_back(TO_CHAR);
        break;
    case BOOL_T:
        if (current_type == DOUBLE_T){compileError("cant convert double to bool");}
        if (current_type == FLOAT_T){compileError("cant convert float to bool");}
        if (current_type == CHAR_T){compileError("cant convert char to bool");}
        if (current_type == STRING_T){compileError("cant convert string to bool");}
        byte_code_consts.back()->code.push_back(TO_BOOL);
        break;
    default:
        compileError("cant cast to invalid type");
        break;
    }
}
Value Compiler::visit(LogicalNotNode& node) {
    node.operand1->accept(*this);
    if (current_type != BOOL_T){
        compileError("logical not expected bool type");
    }
    byte_code_consts.back()->code.push_back(NOT_LOGIC);
}
Value Compiler::visit(AssignmentStatementNode& node) {
}
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