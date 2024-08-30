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

   // currentEnvironment->printEnviroment();

    return Value();
}

Value EvalVisitor::visit(IntLiteralNode& node) {return Value(node.val);}
Value EvalVisitor::visit(FloatLiteralNode& node) {return Value(node.val);}
Value EvalVisitor::visit(DoubleLiteralNode& node) {return Value(node.val);}
Value EvalVisitor::visit(CharLiteralNode& node) {return Value(node.val);}
Value EvalVisitor::visit(StringLiteralNode& node) {return Value(node.val);}
Value EvalVisitor::visit(BoolLiteralNode& node) {return Value(node.val);}


Value EvalVisitor::visit(ParamterNode& node) {return Value();}
Value EvalVisitor::visit(CodeBlockNode& node) {
    if (currentEnvironment->caller == nullptr){
        //if this code block didnt start from a function call make a new enviroment or scope for it
        //with the previous enviroment as the parent. otherwise we will be usign the enviroment setup by the function call
        std::shared_ptr<Environment> newEnv = std::make_shared<Environment>(currentEnvironment);
        currentEnvironment = newEnv;
    }

    //execute code in code block
    for (int i=0; i<node.statements.size(); i++){
        Value val = node.statements[i]->accept(*this);
        //if we are i na function and are retruning a value we will pass up the value
        if (isReturningValue){
            return val;
        }
        if (isBreaking){
            breakAmount--;
            return val;
        }
    }

    if (currentEnvironment->caller == nullptr){
        //if this code block wasnt part of a function call set the enviroment to its parent as we exit scope.
        //there should always be a parent enviroment.
        currentEnvironment = currentEnvironment->parent;
    }

    return Value();
}
Value EvalVisitor::visit(ExpressionNode& node)  {return Value();}
Value EvalVisitor::visit(TypeCastNode& node)  {return Value();}
Value EvalVisitor::visit(LogicalNotNode& node)  {return Value();}
Value EvalVisitor::visit(AssignmentStatementNode& node)  {
    ValueContext varContext = currentEnvironment->getValue(node.identifer);
    if (varContext.value == nullptr){
        if (node.operation != TokenType::ASSIGN_EQU){
            std::cerr << "Error: no varaible named " << node.identifer << " found." << std::endl;
            exit(-1);
        }

        if (node.type == INVALID_TYPE){
            std::cerr << "Error: no varaible named " << node.identifer << " found." << std::endl;
            exit(-1);
        }
        
        Value v = node.expression->accept(*this);
        if (v.type != node.type){
            std::cerr << "Error: variable " << node.identifer << " is type " << node.type << " but value type " << v.type << " assigned." << std::endl;
            exit(-1);
        }

        //no variable but an assignment means we create a new variable
        currentEnvironment->setValue(node.identifer, v);
        return Value();
    }

    if (node.type != INVALID_TYPE){
        std::cerr << "Error: variable " << node.identifer << " is already defined " << std::endl;
        exit(-1);
    }    

    Value v = node.expression->accept(*this);

    //TODO: check for compatible types and operations like adding doubles to ints or something
    if (v.type != varContext.value->type){
        std::cerr << "Error: variable " << node.identifer << " is type " << varContext.value->type << " but value type " << v.type << " used." << std::endl;
        exit(-1);
    }
    //TODO: finish

    return Value();
}

Value EvalVisitor::visit(FuncCallStatementNode& node)  {
    ValueContext funcContext = currentEnvironment->getValue(node.identifier);
    //check if we found a valid function
    if (funcContext.value == nullptr){
        std::cerr << "Error: no function named " << node.identifier << " found." << std::endl;
        exit(-1);
    }
    if (funcContext.value->type != FUNC_DEC_VAL){
        std::cerr << "Error: identifer " << node.identifier << " is not a function." << std::endl;
        exit(-1);
    }

    FuncDecNode* func = funcContext.value->getFuncDec();

    std::cout << func->params.size() << ", " << node.args.size() << std::endl;

    if (func->params.size() != node.args.size()){
        //NOTE: at the moment default values are not supported
        std::cerr << "Error: incorrect number of paramters of function call at "<< node.identifier << std::endl;
        exit(-1);
    }

    std::vector<Value> argVals;
    for (int i=0; i<node.args.size(); i++){
        Value v = node.args[i]->accept(*this);
        argVals.push_back(v);
    }

    for (int i=0; i<node.args.size(); i++){
        if (func->params[i]->type != argVals[i].type){
            std::cerr << "Error: invalid argument types of funciton call "<< node.identifier << "param number:" << i+1 << std::endl;
            exit(-1);
        }
        //TODO: check for arrays and their dimensions
    }

    //make a new enviroment for the function call.
    //parent is parent enviroment of funciton not the callers enviroment
    std::shared_ptr<Environment> newEnv = std::make_shared<Environment>(funcContext.definingEnv,currentEnvironment);
    currentEnvironment = newEnv;
    
    for (int i=0; i<func->params.size(); i++){
        //set the paramte rvaraible up in enviroment
        newEnv->setValue(func->params[i]->identifer, argVals[i]);
    }

    //execute code block of function
    Value v = func->body->accept(*this);
    if (isReturningValue){
        isReturningValue = false;
    }
    //if we are still breaking but not in a loop
    if (isBreaking && breakAmount != 0){
        std::cerr << "Error: too many breaking commands in funciton "<< node.identifier << std::endl;
        exit(-1);
    }
    if (isBreaking && breakAmount == 0){
        isBreaking = false;
    }

    if (v.type != func->type){
        std::cerr << "Error: invalid return type "<< v.type << "should be " << func->type << std::endl;
        exit(-1);
    }

    //set back to orginal enviroment and not function call enviroment
    currentEnvironment = currentEnvironment->caller;

    return v;
}

Value EvalVisitor::visit(ConditionStatementNode& node)  {return Value();}
Value EvalVisitor::visit(ForLoopNode& node)  {return Value();}
Value EvalVisitor::visit(WhileLoopNode& node)  {return Value();}
Value EvalVisitor::visit(ReturnStatementNode& node)  {
    isReturningValue = true;
    Value v = node.expression->accept(*this);
    return v;
}
Value EvalVisitor::visit(BreakStatementNode& node) {
    isBreaking = true;
    
    Value v = node.expression->accept(*this);

    if (v.type == INT_VAL){
        breakAmount = v.getValue<int>();
    }

    return Value();
}

Value EvalVisitor::visit(FuncDecNode& node) {
    FuncDecNode* decPtr = &node;
    Value dec = Value(decPtr);

    if(currentEnvironment->getValue(node.identifier).value != nullptr){
        //TODO: expand on this to account for function overloading
        std::cerr << "Error: function redefinition: " << node.identifier << std::endl;
        exit(-1); 
    }
    currentEnvironment->setValue(node.identifier, dec);

    return Value();
}

Value EvalVisitor::visit(ContinueStatementNode& node) {return Value();}
Value EvalVisitor::visit(ArrayIndexingNode& node) {return Value();}
Value EvalVisitor::visit(ArrayGetElementNode& node) {return Value();}
Value EvalVisitor::visit(IdentifierNode& node)  {
    ValueContext varContext = currentEnvironment->getValue(node.identifier);
    if (varContext.value == nullptr){
        std::cerr << "Error: identifier " << node.identifier << std::endl;
        exit(-1); 
    }
    //dereference since it is pointer
    Value v = *varContext.value;
    return v;
}
Value EvalVisitor::visit(IncDecStatementNode& node)  {return Value();}
Value EvalVisitor::visit(ArrayAssignmentNode& node) {return Value();}
Value EvalVisitor::visit(ImportStatementNode& node) {return Value();}
Value EvalVisitor::visit(ElementAssignmentNode& node) {return Value();}
Value EvalVisitor::visit(ArrayBlockNode& node) {return Value();}