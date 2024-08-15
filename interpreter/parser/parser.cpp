#include "parser.h"
#include <iostream>
#include <stdexcept>


Token Parser::eat(){
    Token eaten = currentToken;
    currIndex++;
    //if we went passed the last token (should be eof) then we can return it without trying to set current token
    if (currIndex > tokens.size()-1){
        return eaten;
    }
    currentToken = tokens[currIndex];
    return eaten;
}

Token Parser::vomit(){
    Token vomitted = currentToken;
    currIndex--;
    //this really should not happen
    if (currIndex < 0){
        std::cerr << "How did you even backtrack so far? " << "currIndex: " << currIndex
        << currentToken.text << currentToken.startPos << std::endl;
        exit(-1);
    }
    currentToken = tokens[currIndex];
    return vomitted;
}

Token Parser::lookAhead(int a=1){
    if (tokens.size() > currIndex+a){
        return tokens[currIndex+a];
    }
    std::cerr << "Error cant look that far ahead " << currentToken.text << " " 
    << currentToken.startPos << "currIndex: "<< currIndex << "lookahead: " << a << std::endl; 
    exit(-1);
}

//checks for dataType specifiers like 'int'
DataType Parser::dataDeclaration(){
    DataType dataType;
    if (currentToken == KW_INT){
        dataType = INT_T;
        return dataType;
    }
    if (currentToken == KW_DOUBLE){
        dataType = DOUBLE_T;
        return dataType;
    }
    if (currentToken == KW_FLOAT){
        dataType = FLOAT_T;
        return dataType;
    }
    if (currentToken == KW_BOOL){
        dataType = BOOL_T;
        return dataType;
    }
    if (currentToken == KW_STRING){
        dataType = STRING_T;
        return dataType;
    }
    if (currentToken == KW_VOID){
        dataType = VOID_T;
        return dataType;
    }
    if (currentToken == KW_CHAR){
        dataType = CHAR_T;
        return dataType;
    }
    return INVALID_TYPE;
    
}

std::unique_ptr<ParamterNode> Parser::parameter(){
    if (currentToken != FLUFF){
        return nullptr; //may just be a function without paramters
    }
    eat(); //eat fluff keyword
    DataType dataType = dataDeclaration();
    if (dataType == INVALID_TYPE){
        std::cerr << "Error: invalid paramter defenition at " << currentToken.text << " " << currentToken.startPos << std::endl;
        exit(-1);
    }
    eat(); //eat data type token
    int dim = 0;
    while (currentToken == LSQ_BRACE){ //if there are sqr braces for arrays
        eat(); //eat left brace
        if (currentToken != RSQ_BRACE){
            std::cerr << "Error: invalid paramter defenition at " << currentToken.text << " " << currentToken.startPos << std::endl;
            exit(-1);
        }
        eat(); //eat right brace
        dim++;
    }

    if (currentToken != IDENTIFIER){
        std::cerr << "Error: invalid paramter defenition at " << currentToken.text << " " << currentToken.startPos << std::endl;
        exit(-1);
    }
    std::unique_ptr<ParamterNode> param(new ParamterNode());
    param->type = std::move(dataType);
    param->identifer = currentToken.text;
    param->dim = dim; //set dimensions of array. 0 means it isnt an array
    eat();
    return param;
}

std::unique_ptr<TypeCastNode> Parser::typeCast(){
    if (currentToken != LT){ //if current token is not '<'
        return nullptr; //not a type cast may be another type of expression
    }
    eat(); //eat the '<' token
    DataType type = dataDeclaration();
    if (type == INVALID_TYPE){
        //error as no other expression would start with '<'
        std::cerr << "Error Invalid type cast at " << currentToken.text << currentToken.startPos << std::endl;
        exit(-1);
    }
    eat(); //eat type token
    if (currentToken != GT){
        std::cerr << "Error Invalid type cast at " << currentToken.text << currentToken.startPos << std::endl;
        exit(-1);
    }
    eat(); //eat '>'

    std::unique_ptr<Node> exp = expression();
    if (exp == nullptr){
        std::cerr << "Error Invalid type cast at " << currentToken.text << currentToken.startPos << std::endl;
        exit(-1);
    }
    std::unique_ptr<TypeCastNode> castNode(new TypeCastNode);
    castNode->type = type;
    castNode->expression = std::move(exp);
    return castNode;
}

std::unique_ptr<FuncCallStatementNode> Parser::callFunction(){
    if (currentToken == IDENTIFIER && lookAhead(1) == LPAREN){

        std::unique_ptr<FuncCallStatementNode> exp(new FuncCallStatementNode);
        exp->identifier = currentToken.text;
        eat(); //eat identifier
        eat(); //eat parentheses
        if (currentToken == RPAREN){
            eat();
            return exp;
        }
        //expression checks to see if the expression was valid and errors before returning if not
        std::unique_ptr<Node> arg = expression();
        (exp->args).push_back(std::move(arg));
        //keep getting arguments until RPAREN. if there is no RPAREn then an erro in expression will be reached
        while (currentToken != RPAREN){
            //if the next was not a comma then there is an error
            if (currentToken != COMMA){
                std::cerr << "Error: expected comma at " << currentToken.text << " " << currentToken.startPos << std::endl;
                exit(-1);
            }
            eat(); //eat comma
            //expression checks to see if the expression was valid and errors before returning if not
            arg = expression(); //get the next arg/expression
            (exp->args).push_back(std::move(arg));
        }
        eat(); //eat RPAREN
        return exp;

    }
    else{
        return nullptr;
    }
}


std::unique_ptr<ArrayIndexingNode> Parser::arrayIndices(){
    if (currentToken != LSQ_BRACE){
        return nullptr; //might be another kind of statement or expression
    }
    eat();
    
    std::unique_ptr<Node> exp = expression();
    
    if (currentToken != RSQ_BRACE){
        std::cerr << "Error no closing square brace at " << currentToken.text << currentToken.startPos << std::endl;
        exit(-1);
    }
    eat();
    

    std::unique_ptr<ArrayIndexingNode> node(new ArrayIndexingNode);
    node->indices.push_back(std::move(exp));

    //keep going through all indices
    while(currentToken == LSQ_BRACE){
        eat();
        std::unique_ptr<Node> exp = expression();
        node->indices.push_back(std::move(exp));
        if (currentToken != RSQ_BRACE){
            std::cerr << "Error no closing square brace at " << currentToken.text << currentToken.startPos << std::endl;
            exit(-1);
        }
        eat();
    }
    return node;
}

std::unique_ptr<ArrayGetElementNode> Parser::arrayGetElement(){
    if (currentToken != IDENTIFIER){
        return nullptr; //might be another kind of statement or expression
    }
    std::unique_ptr<ArrayGetElementNode> node(new ArrayGetElementNode);
    node->identifer = currentToken.text;
    eat();
    std::unique_ptr<ArrayIndexingNode> indices = arrayIndices();
    if (indices == nullptr){
        vomit();
        return nullptr; //again could still be another kind of statement or expression
    }
    node->indeices = std::move(indices);
    return node;
}

std::unique_ptr<Node> Parser::simpleExpression(){
    if (currentToken == INT){
        std::unique_ptr<IntLiteralNode> node(new IntLiteralNode);
        node->val = stoi(currentToken.text);
        eat();

        return node;
    }
    if (currentToken == DOUBLE){
        std::unique_ptr<DoubleLiteralNode> node(new DoubleLiteralNode);
        node->val = stod(currentToken.text);
        eat();
        return node;
    }
    if (currentToken == FLOAT){
        std::unique_ptr<FloatLiteralNode> node(new FloatLiteralNode);
        node->val = stof(currentToken.text);
        eat();
        return node;
    }
    if (currentToken == STRING){
        std::unique_ptr<StringLiteralNode> node(new StringLiteralNode);
        node->val = currentToken.text;
        eat();
        return node;
    }
    if (currentToken == CHAR){
        std::unique_ptr<CharLiteralNode> node(new CharLiteralNode);
        node->val = currentToken.text[0];
        eat();
        return node;
    }
    if (currentToken == TRUE){
            std::unique_ptr<BoolLiteralNode> node(new BoolLiteralNode);
        node->val = true;
        eat();
        return node;
    }
    if (currentToken == FALSE){
        std::unique_ptr<BoolLiteralNode> node(new BoolLiteralNode);
        node->val = false;
        eat();
        return node;
    }
    if (currentToken == IDENTIFIER){
        std::unique_ptr<IdentifierNode> node(new IdentifierNode);
        node->identifier = currentToken.text;
        eat();
        return node;
    }
    return nullptr;
}

std::unique_ptr<Node> Parser::primaryExpression(){
    std::unique_ptr<Node> exp = callFunction();
    if (exp != nullptr){
        return exp;
    }
    //if it was null might be another expression
    exp = arrayGetElement();
    if (exp != nullptr){
        return exp;
    }
    exp = simpleExpression();
    if (exp != nullptr){
        return exp;
    }
    if (currentToken == LPAREN){
        eat(); //eat apren
        exp = expression(); //get an expression
        if (currentToken == RPAREN){
            eat();
            return exp;
        }
        else{
            std::cerr << "Error: expected ')' at " << currentToken.text << " " << currentToken.startPos << std::endl;
            exit(-1);
        }
    }
    //if non of the above are found then there is nothing else that could be a valid expression and returning
    // nullptr is not needed. 
    std::cerr << "Error: no valid expression found at " << currentToken.text << " " << currentToken.startPos << std::endl;
    exit(-1);
}

std::unique_ptr<Node> Parser::exponentialExpression(){
    std::unique_ptr<Node> term = primaryExpression();
    if (term == nullptr){
        std::cerr << "Error: shouldnt happen primaryExpression should always return a node or error beofre returning " <<
        currentToken.text << " " << currentToken.startPos << std::endl;
        exit(-1);
    }

    //pass node up if there is no exponent operator
    if (currentToken !=  EXP){ return term;}
    
    std::unique_ptr<ExpressionNode> exp(new ExpressionNode);
    exp->operand1 = std::move(term);

    //set operation
    exp->operation = currentToken.type;
    eat(); //eat logic operator token 

    term = primaryExpression();
    if (term == nullptr){
        std::cerr << "Error: should not happen. primaryExpression should return a node or have error before returning "
        << currentToken.text << currentToken.startPos << std::endl;
        exit(-1);
    }

    exp->operand2 = std::move(term);
    return exp;
}

std::unique_ptr<Node> Parser::multiplicativeExpression(){
    std::unique_ptr<Node> term = exponentialExpression();
    if (term == nullptr){
        std::cerr << "Error: shouldnt happen exponentialExpression should always return a node or error beofre returning " <<
        currentToken.text << " " << currentToken.startPos << std::endl;
        exit(-1);
    }

    //pass node up if there is no multiplicative operator
    if (currentToken != STAR && currentToken != DIV && currentToken != MOD ){ return term;}
    
    std::unique_ptr<ExpressionNode> exp(new ExpressionNode);
    exp->operand1 = std::move(term);

    //set operation
    exp->operation = currentToken.type;
    eat(); //eat logic operator token 

    term = exponentialExpression();
    if (term == nullptr){
        std::cerr << "Error: should not happen. exponentialExpression should return a node or have error before returning "
        << currentToken.text << currentToken.startPos << std::endl;
        exit(-1);
    }

    exp->operand2 = std::move(term);
    return exp;
}

std::unique_ptr<Node> Parser::additiveExpression(){
    std::unique_ptr<Node> term = multiplicativeExpression();
    if (term == nullptr){
        std::cerr << "Error: shouldnt happen multiplicativeExpression should always return a node or error beofre returning " <<
        currentToken.text << " " << currentToken.startPos << std::endl;
        exit(-1);
    }

    //pass node up if there is no additive operator
    if (currentToken != ADD && currentToken != SUB ){ return term;}
    
    std::unique_ptr<ExpressionNode> exp(new ExpressionNode);
    exp->operand1 = std::move(term);

    //set operation
    exp->operation = currentToken.type;
    eat(); //eat logic operator token 

    term = multiplicativeExpression();
    if (term == nullptr){
        std::cerr << "Error: should not happen. multiplicativeExpression should return a node or have error before returning "
        << currentToken.text << currentToken.startPos << std::endl;
        exit(-1);
    }

    exp->operand2 = std::move(term);
    return exp;
}


std::unique_ptr<Node> Parser::relationalExpression(){
    std::unique_ptr<Node> term = additiveExpression();
    if (term == nullptr){
        std::cerr << "Error: shouldnt happen additiveExpression should always return a node or error beofre returning " <<
        currentToken.text << " " << currentToken.startPos << std::endl;
        exit(-1);
    }

    //pass node up if there is no relational operator
    if (currentToken != LT && currentToken != GT && currentToken != LEQ && 
        currentToken != GEQ && currentToken != EQ && currentToken != NEQ){ return term;}
    
    std::unique_ptr<ExpressionNode> exp(new ExpressionNode);
    exp->operand1 = std::move(term);

    //set operation
    exp->operation = currentToken.type;
    eat(); //eat relational operator token 

    term = additiveExpression();
    if (term == nullptr){
        std::cerr << "Error: should not happen. additiveExpression should return a node or have error before returning "
        << currentToken.text << currentToken.startPos << std::endl;
        exit(-1);
    }

    exp->operand2 = std::move(term);
    return exp;

}

std::unique_ptr<Node> Parser::logicalNot(){
    bool isNot = false;
    if (currentToken == NOT){
        isNot = true;
        eat(); //eat token
    }

    std::unique_ptr<Node> relExp = relationalExpression();
    if (relExp == nullptr){
        std::cerr << "Error: shouldnt happen relationalExpression should always return a node or error beofre returning " <<
        currentToken.text << " " << currentToken.startPos << std::endl;
        exit(-1);
    }

    if (isNot){
        std::unique_ptr<LogicalNotNode> node(new LogicalNotNode);
        node->operand1 = std::move(relExp);
        return node;
    }
    return relExp;
}

std::unique_ptr<Node> Parser::logicalExpression(){
    std::unique_ptr<Node> term = logicalNot();
    if (term == nullptr){
        std::cerr << "Error: should not happen. logicalNot should return a node or have error before returning "
        << currentToken.text << currentToken.startPos << std::endl;
        exit(-1);
    }
    //if no logical expresison term pass node up
    if (currentToken != AND && currentToken != OR){ return term; }


    std::unique_ptr<ExpressionNode> exp(new ExpressionNode);
    exp->operand1 = std::move(term);

    //set operation to 'and' or 'or'
    exp->operation = currentToken.type;
    eat(); //eat logic operator token 

    term = logicalNot();
    if (term == nullptr){
        std::cerr << "Error: should not happen. logicalNot should return a node or have error before returning "
        << currentToken.text << currentToken.startPos << std::endl;
        exit(-1);
    }

    exp->operand2 = std::move(term);
    return exp;
    

}

std::unique_ptr<Node> Parser::expression(){
    std::unique_ptr<TypeCastNode> castNode = typeCast();
    if (castNode != nullptr){
        return castNode;
    }
    std::unique_ptr<Node> logicExp = logicalExpression();
    if (logicExp == nullptr){
        std::cerr << "Error: this shouldnt happen. logicalExpression should alway return a node or an error happens furhter down. happend at " 
        << currentToken.text << currentToken.startPos << std::endl;
        exit(-1);
    }
    return logicExp;
}

std::unique_ptr<AssignmentStatementNode> Parser::assignExpression(){
    std::unique_ptr<AssignmentStatementNode> as(new AssignmentStatementNode);
    as->type = INVALID_TYPE; //there may be no type in statement. semantic analysis wil lreveal if there should be or not

    if (currentToken == FLUFF){
        eat(); //eat fluff token
        DataType type = dataDeclaration();
        if (type == INVALID_TYPE){ //if there is fluff then there should be valid data type
            std::cerr << "Invalid type at " << currentToken.text << " " << currentToken.startPos << std::endl;
            exit(-1);
        }
        as->type = type;
        eat(); //eat data type declaration token
        if (currentToken != IDENTIFIER){
            std::cerr << "No identifier at " << currentToken.text << " " << currentToken.startPos << std::endl;
            exit(-1);
        }
    }
    else if (currentToken != IDENTIFIER){
        return nullptr; //if there was not at an identifier at begining of statement then there may be a different statemtn
    }

    as->identifer = currentToken.text; //set identifer
    eat(); //identifier

    switch(currentToken.type){
        case ASSIGN_EQU:
            as->operation = ASSIGN_EQU;
            break;
        case ADD_EQ:
            as->operation = ADD_EQ;
            break;
        case SUB_EQ:
            as->operation = SUB_EQ;
            break;
        case MUL_EQ:
            as->operation = MUL_EQ;
            break;
        case DIV_EQ:
            as->operation = DIV_EQ;
            break;
        case EXP_EQ:
            as->operation = EXP_EQ;
            break;
        case MOD_EQ:
            as->operation = MOD_EQ;
            break;
        default:
            //if you reached this point and this is invalid then it means there was no data declaration
            //so might still be another type of statemnt starting with an identifier
            if (as->type == INVALID_TYPE){ 
                vomit(); //uneat the identifer token
                return nullptr;
            }
            else{ //if there was a data declaration
                std::cerr << "Error no assignment operation at " << currentToken.text << " " << currentToken.startPos << std::endl;
                exit(-1);
            }
    }
    eat(); //eat operator token
    
    std::unique_ptr<Node> exp = expression(); //get an expression
    if (exp == nullptr){
        std::cerr << "Error expected expression at " << currentToken.text << " " << currentToken.startPos << std::endl;
        exit(-1);
    }
    as->expression = std::move(exp); //set expression child of assignment node
    return as;
}

std::unique_ptr<AssignmentStatementNode> Parser::assignStatement(){
    
    std::unique_ptr<AssignmentStatementNode> as = assignExpression();
    if (as == nullptr){return nullptr;} //if it reutrned null it means it might be another statemement
    if (currentToken != SEMICOLON){
        std::cerr << "Error: expected ';' at " << currentToken.text << " " << currentToken.startPos << std::endl;
        exit(-1);
    }
    eat();
    return as;
}

std::unique_ptr<FuncCallStatementNode> Parser::funcCallStatment(){
    std::unique_ptr<FuncCallStatementNode> callExp = callFunction();
    if (callExp == nullptr){
        return nullptr;
    }
    if (currentToken != SEMICOLON){
        std::cerr << "Error: expected ';' at " << currentToken.text << " " << currentToken.startPos << std::endl;
        exit(-1);
    }
    eat();
    return callExp;
}

std::unique_ptr<CodeBlockNode> Parser::elseStatement(){
    if (currentToken == WHIMPER && lookAhead(1) == LBRACE){
        eat(); //consume whimper but not brace as codebLOCK DOES THAT
        std::unique_ptr<CodeBlockNode> block = codeBlock();
        return block;
    }
    return nullptr;
}

std::unique_ptr<ConditionStatementNode> Parser::elseIfStatement(){
    if (currentToken == WHIMPER && lookAhead(1) == SNIFF){
        eat(); //consume whimper
        eat(); //consume sniff
        std::unique_ptr<ConditionStatementNode> statement = conditionBody();
        return statement;
    }
    return nullptr;
}

std::unique_ptr<ConditionStatementNode> Parser::conditionBody(){
    std::unique_ptr<Node> exp = expression();
    std::unique_ptr<CodeBlockNode> block = codeBlock();

    std::unique_ptr<ConditionStatementNode> statement(new ConditionStatementNode);
    statement->expression = std::move(exp);
    statement->block = std::move(block);
    statement->elseBlock = nullptr;

    std::unique_ptr<CodeBlockNode> elseBlock = elseStatement();
    if (elseBlock != nullptr){
        statement->elseBlock = std::move(elseBlock);
        return statement;
    }

    std::unique_ptr<ConditionStatementNode> other = elseIfStatement();
    if (other != nullptr){
        statement->elseBlock = std::move(other);
    }

    return statement;
}

std::unique_ptr<ConditionStatementNode> Parser::conditionStatement(){
    if (currentToken != SNIFF){
        return nullptr;
    }
    eat();
    std::unique_ptr<ConditionStatementNode> node = conditionBody();
    return node;
}

std::unique_ptr<ContinueStatementNode> Parser::continueStatement(){
    if (currentToken != HUNT){
        return nullptr;
    }
    eat();
    if (currentToken != SEMICOLON){
        std::cerr << "Error: expected semicolon at " << currentToken.text << " " << currentToken.startPos << std::endl;
        exit(-1);
    }
    std::unique_ptr<ContinueStatementNode> st(new ContinueStatementNode);
    return st;
}

std::unique_ptr<BreakStatementNode> Parser::breakStatement(){
    if (currentToken != POUNCE){
        return nullptr;
    }
    eat();
    std::unique_ptr<Node> exp = expression();
    if (currentToken != SEMICOLON){
        std::cerr << "Error: expected semicolon at " << currentToken.text << " " << currentToken.startPos << std::endl;
        exit(-1);
    }
    std::unique_ptr<BreakStatementNode> bs(new BreakStatementNode);
    bs->expression = std::move(exp);
    return bs;
}

std::unique_ptr<ReturnStatementNode> Parser::returnStatement(){
    if (currentToken != BARK){
        return nullptr;
    }
    eat();
    std::unique_ptr<Node> exp = expression();
    if (currentToken != SEMICOLON){
        std::cerr << "Error: expected semicolon at " << currentToken.text << " " << currentToken.startPos << std::endl;
        exit(-1);
    }
    std::unique_ptr<ReturnStatementNode> bs(new ReturnStatementNode);
    bs->expression = std::move(exp);
    return bs;
}

std::unique_ptr<IncDecStatementNode> Parser::incDec(){
    if (currentToken != IDENTIFIER){
        return nullptr;
    }
    std::unique_ptr<IncDecStatementNode> node(new IncDecStatementNode);
    node->identifer = currentToken.text;
    eat();

    if (currentToken == INC){
        node->operation = true;
    }
    else if (currentToken == DEC){
        node->operation = false;
    }
    else{
        std::cerr << "Error: expected '++' or '--' at " << currentToken.text << " " << currentToken.startPos << std::endl;
        exit(-1);
    }
    eat();
    return node;

}

std::unique_ptr<ForLoopNode> Parser::forLoop(){
    if (currentToken != PROWL){
        return nullptr;
    }
    eat(); //eat prowl
    if (currentToken != LPAREN){
        std::cerr << "Error: expected '(' at " << currentToken.text << " " << currentToken.startPos << std::endl;
        exit(-1);
    }
    eat(); //eat parent
        std::cout << currentToken.text << std::endl;
    std::unique_ptr<AssignmentStatementNode> ae = assignExpression();

    if (ae == nullptr){
        std::cerr << "Error: invalid assignment expression at " << currentToken.text << " " << currentToken.startPos << std::endl;
    }
    if (currentToken != SEMICOLON){
        std::cerr << "Error: expected ';' at " << currentToken.text << " " << currentToken.startPos << std::endl;
        exit(-1);
    }
    eat(); //eat semicolon


    std::unique_ptr<Node> exp = expression();

    if (currentToken != SEMICOLON){
        std::cerr << "Error: expected ';' at " << currentToken.text << " " << currentToken.startPos << std::endl;
        exit(-1);
    }
    eat(); //eat semicolon

    std::unique_ptr<Node> ae2 = assignExpression();
    if (ae2 == nullptr){
        //TODO: check for inc and dec statement
        ae2 = incDec();
        if (ae2 == nullptr){
            std::cerr << "Error: no third statement in for loop at " << currentToken.text << " " << currentToken.startPos << std::endl;
            exit(-1);
        }
    }

    if (currentToken != RPAREN){
        std::cerr << "Error: expected ')' at " << currentToken.text << " " << currentToken.startPos << std::endl;
        exit(-1);
    }
    eat();

    std::unique_ptr<CodeBlockNode> block = codeBlock();

    std::unique_ptr<ForLoopNode> node(new ForLoopNode);
    node->assignSatement = std::move(ae2);
    node->condition = std::move(exp);
    node->block = std::move(block);

    return node;
}



std::unique_ptr<Node> Parser::statement(){
    std::unique_ptr<AssignmentStatementNode> assignStatementNode = assignStatement();
    if (assignStatementNode != nullptr){
        return assignStatementNode;
    }

    std::unique_ptr<FuncCallStatementNode> callStatment = funcCallStatment();
    if (callStatment != nullptr){
        return callStatment;
    }
    std::unique_ptr<ConditionStatementNode> conditional = conditionStatement();
    if (conditional != nullptr){
        return conditional;
    }

    std::unique_ptr<ForLoopNode> forLoopStatement = forLoop();
    if (forLoopStatement != nullptr){
        return forLoopStatement;
    }

    return nullptr;
    //TODO: check for other statements
}

std::unique_ptr<CodeBlockNode> Parser::codeBlock(){
    if (currentToken != LBRACE){
        std::cerr << "Error: Missing opening bracket at " << currentToken.text << " " << currentToken.startPos << std::endl;
        exit(-1);
    }
    eat(); //eat opening brace
    std::unique_ptr<CodeBlockNode> block(new CodeBlockNode);
    while (currentToken != RBRACE){
        std::unique_ptr<Node> Statement = statement();
        if (Statement == nullptr){
            std::cerr << "Error: no known statement at " << currentToken.text << " " << currentToken.startPos << std::endl;
            exit(-1);
        }
        (block->statements).push_back(std::move(Statement));
    }
    eat(); //eat closing brace
    return block;

}

std::unique_ptr<FuncDecNode> Parser::functionDeclaration(){
    DataType dataType = dataDeclaration();
    if (dataType == INVALID_TYPE){
        //no data type keyword found but doesnt mean invalid syntax return and try another statemnt
        return nullptr; 
    }
    eat(); //eat data type token
    if (currentToken != TRICK){
        //error and exit. 
        //no other statements have a dataType as the first token
        // so if there was one then it must be an attempt a function declaration
        std::cerr << "Error: invalid function defenition at " << currentToken.text << " " << currentToken.startPos << std::endl;
        exit(-1);
    }
    eat(); //eat plunge token
    if (currentToken != IDENTIFIER){
        std::cerr << "Error: invalid function defenition at " << currentToken.text << " " << currentToken.startPos << std::endl;
        exit(-1);
    }
    std::unique_ptr<FuncDecNode> declaration(new FuncDecNode());
    declaration->identifier = currentToken.text;
    eat(); //eat identifier token (function name)
    if (currentToken != LPAREN){
        std::cerr << "Error: invalid function defenition at " << currentToken.text << " " << currentToken.startPos << std::endl;
        exit(-1);
    }
    eat(); //eat '('
    
    std::unique_ptr<ParamterNode> param = parameter();
    //if there is a=paramter add it and check for another paramter until there are none
    if (param != nullptr){
        (declaration->params).push_back(std::move(param));
        //comma after paramter indicates another paramter
        while (currentToken == COMMA){
            eat(); //eat comma
            param = parameter();
            if (param == nullptr){
                std::cerr << "Error: invalid paramter defenition at " << currentToken.text << " " << currentToken.startPos << std::endl;
                exit(-1);
            }
            (declaration->params).push_back(std::move(param));
        }
    }

    if (currentToken != RPAREN){
        std::cerr << "Error: invalid function defenition at " << currentToken.text << " " << currentToken.startPos << std::endl;
        exit(-1);
    }
    eat();
    std::unique_ptr<CodeBlockNode> body = codeBlock();

    
    declaration->body = std::move(body);
    declaration->type = std::move(dataType);
    return declaration;
}

std::unique_ptr<ProgramNode> Parser::program(){
        std::unique_ptr<ProgramNode> prog(new ProgramNode);
    while (currentToken != END_FILE){
        std::unique_ptr<FuncDecNode> funcDec = functionDeclaration();
        if (funcDec != nullptr){
            (prog->statements).push_back(std::move(funcDec));
        }
        if (currentToken == END_FILE){break;}

        std::unique_ptr<Node> stmnt = statement();
        if (stmnt != nullptr){
            (prog->statements).push_back(std::move(stmnt));
        }
    }
    eat();
    return prog;
}


//pass token list by reference
Parser::Parser(std::vector<Token> &tokens) {
    this->tokens = tokens;
    currIndex = 0;
    currentToken = (this->tokens)[currIndex];
}

std::unique_ptr<ProgramNode> Parser::parse(){
    return program();
}
