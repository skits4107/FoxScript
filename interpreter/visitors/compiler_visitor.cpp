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
    if (variables.find(name) != variables.end()){
        compileError("variable "+name+" already defined.");
    }
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
    DataType op1_type = current_type;

    node.operand2->accept(*this);
    DataType op2_type = current_type;

    //TODO: add type checking here
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
    current_type = node.type;
}
Value Compiler::visit(LogicalNotNode& node) {
    node.operand1->accept(*this);
    if (current_type != BOOL_T){
        compileError("logical not expected bool type");
    }
    byte_code_consts.back()->code.push_back(NOT_LOGIC);
}
Value Compiler::visit(AssignmentStatementNode& node) {
    std::string name = function_scope.back() + node.identifer;

    //if the variable exists and is in a higher scope then it should error
    if (variables.find(name) != variables.end() && variables[name].scope_level > current_scope_level){
        compileError("variable "+name+" no longer in scope.");
    }

    node.expression->accept(*this);

    if (current_type != node.type){
        compileError("variable "+name+" expresion returns wrong type");
    }

    // if it is a new variable add it to map.
    if (variables.find(name) == variables.end()){
        IdentifierInfo info(current_scope_level, variable_arg_reference);
        variables[name] = info;
    }

    byte_code_consts.back()->code.push_back(SAVE_VAR);
    byte_code_consts.back()->code.push_back((int8_t)variable_arg_reference);

    variable_arg_reference++;
}
Value Compiler::visit(FuncCallStatementNode& node) {
    // NOTES for later:
    // check if function has been register/compiled.
    // check for default/built in functions
    // check if calling it is in scope.
    // compile arg expressions one by one and check each type. (may require storing extra meta info on function defenitions)
    // call function.
    // set current_type to function return type. (Again may require sotring meta informaiton during compilation)
}
Value Compiler::visit(ConditionStatementNode& node) {
    node.accept(*this);
    if (current_type != BOOL_T){
        compileError("Condiiotnal requires a bool");
    }

    
}
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