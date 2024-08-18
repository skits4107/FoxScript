#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>
#include "../tokens/token.h"
#include "../nodes/concrete_nodes.h"

class Parser {
private:
    Token currentToken;
    std::vector<Token> tokens;
    int currIndex;

    Token eat();
    Token vomit();
    Token lookAhead(int a = 1);
    DataType dataDeclaration();
    std::unique_ptr<ParamterNode> parameter();
    std::unique_ptr<TypeCastNode> typeCast();
    std::unique_ptr<FuncCallStatementNode> callFunction();
    std::unique_ptr<ArrayIndexingNode> arrayIndices();
    std::unique_ptr<ArrayGetElementNode> arrayGetElement();
    std::unique_ptr<Node> simpleExpression();
    std::unique_ptr<Node> primaryExpression();
    std::unique_ptr<Node> exponentialExpression();
    std::unique_ptr<Node> multiplicativeExpression();
    std::unique_ptr<Node> additiveExpression();
    std::unique_ptr<Node> relationalExpression();
    std::unique_ptr<Node> logicalNot();
    std::unique_ptr<Node> logicalExpression();
    std::unique_ptr<Node> expression();
    std::unique_ptr<AssignmentStatementNode> assignExpression();
    std::unique_ptr<AssignmentStatementNode> assignStatement();
    std::unique_ptr<FuncCallStatementNode> funcCallStatment();
    std::unique_ptr<CodeBlockNode> elseStatement();
    std::unique_ptr<ConditionStatementNode> elseIfStatement();
    std::unique_ptr<ConditionStatementNode> conditionBody();
    std::unique_ptr<ConditionStatementNode> conditionStatement();
    std::unique_ptr<ContinueStatementNode> continueStatement();
    std::unique_ptr<BreakStatementNode> breakStatement();
    std::unique_ptr<ReturnStatementNode> returnStatement();
    std::unique_ptr<ImportStatementNode> importStatement();
    std::unique_ptr<IncDecStatementNode> incDec();
    std::unique_ptr<ForLoopNode> forLoop();
    std::unique_ptr<WhileLoopNode> whileLoop();
    std::unique_ptr<ArrayBlockNode> arrayBlock();
    std::unique_ptr<ElementAssignmentNode> elementAssignment();
    std::unique_ptr<ArrayAssignmentNode> arrayDeclarationStatement();
    std::unique_ptr<IncDecStatementNode> incDecStatement();
    std::unique_ptr<Node> statement();
    std::unique_ptr<CodeBlockNode> codeBlock();
    std::unique_ptr<FuncDecNode> functionDeclaration();
    std::unique_ptr<ProgramNode> program();

public:
    Parser(std::vector<Token>& tokens);
    std::unique_ptr<ProgramNode> parse();
};

#endif PARSER_H