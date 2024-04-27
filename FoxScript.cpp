#include <iostream>
#include <vector>
#include <string>
#include <cctype>  // For isspace()
#include <fstream>
#include <memory>
#include <any>

/*
    sniff = if
    whimper = else
    bark = return
    fluff = var/let
    plunge = function/def
    pack = class
    hunt = for
    chase = while
    burrow = struct
    inherit = extends
    cub = new
    growl = private
    guarded = protected
    show = public
    kitsune = any
    den = static
    vanish = delete
    territory = namespace
    fox = self/this (pass by reference and not pointer)
    stop = break
    pounce = continue
    forage = import
    seek = elif




example syntax:

forage fileName/libraryName

burrow Point{
    show fluff double x = 0;
    show fluff double y = 0;

    // no constructors
}

pack Animal{
    growl fluff string name = "";
    growl fluff int age = 0;
    growl fluff string sound = "";
    
    show Animal(fluff string name, fluff int age, fluff string sound){
        fox.name = name;
        fox.age = age;
        fox.sound - sound;
    }

    show void plunge makeSound(){
        howl(name+" went "+sound);
    }
}

int plunge add(fluff int a, fluff int b){
    bark a+b;
}

int plunge main(fluff int argc, fluff char** argv){
    fluff int a = 10;
    fluff int b = 5;
    fluff int c = a+b;
    fluff char character = 'a';
    fluff string str = "hi";
    fluff int d = add(a, c);
    fluff Animal doggy = Animal("bob", 15, "bark");
    fluff Point* p = cub Point();
    p->x = 20.0;
    p->y = 50.0;
    fluff int charInt = (int)character;


    hunt(fluff int i=0; i<=c; i++){
        sniff(i % 2 ==0){
            howl("even");
        }
        whimper{
            howl("odd");
        }
    }

    vanish p;

    bark 0;
}
*/
enum TokenType {
    // Literals
    INT, FLOAT, STRING, CHAR, DOUBLE,

    // Keywords
    SNIFF, WHIMPER, HUNT, CHASE, BARK, TRUE, FALSE, CUB, PLUNGE, FOX, 
    BURROW, INHERIT, GROWL, SHOW, KITSUNE, SEEK,
    DEN, FLUFF, TERRITORY, PACK, GUARDED, STOP, POUNCE, FORAGE,

    KW_INT,    // Keyword for integer type declaration
    KW_FLOAT,  // Keyword for float type declaration
    KW_DOUBLE, // Keyword for double type declaration
    KW_CHAR, // Keyword for char type declaration
    KW_STRING,
    KW_VOID,
    KW_BOOL,

    // Operators
    ADD, SUB, STAR, DIV, 
    EQ, NEQ, LT, GT, LEQ, GEQ, 
    AND, OR, NOT, MOD, INC, DEC, 
    EXP, ASSIGN_EQU, ADD_EQ, SUB_EQ,
    MUL_EQ, DIV_EQ, EXP_EQ, MOD_EQ,

    // Delimiters
    COMMA, SEMICOLON, LPAREN, RPAREN, LBRACE, RBRACE, LSQ_BRACE, RSQ_BRACE,

    // Identifiers
    IDENTIFIER,

    //pointers and memory
    VANISH,
    ARROW_OP,
    // End of File
    END_FILE
};

struct Token{
    TokenType type;
    std::string text;
    int startPos;

    Token(){
        type = END_FILE;
        text = "<EOF>";
        startPos = 0;
    }

    Token(TokenType type, std::string text, int startPos){
        this->type = type;
        this->text = text;
        this->startPos = startPos;
    }

    bool operator==(TokenType tpe){
        return type == tpe;
    }
     bool operator!=(TokenType tpe){
        return type != tpe;
    }
};




//retruns token type of keywords (true, false, plunge, fluff, int, etc) otherwise it retruns identifer
TokenType proccessKeyWord(std::string text){
     if (text == "true"){
        return TRUE;
    }
    if (text == "false"){
        return FALSE;
    }
    if (text == "int"){
        return KW_INT;
    }
    if (text == "double"){
        return KW_DOUBLE;
    }
    if (text == "char"){
        return KW_INT;
    }
    if (text == "float"){
        return KW_FLOAT;
    }
    if (text == "string"){
        return KW_STRING;
    }
    if (text == "void"){
        return KW_VOID;
    }
    if (text == "bool"){
        return KW_BOOL;
    }
    if (text == "sniff"){
        return SNIFF;
    }
    if (text == "whimper"){
        return WHIMPER;
    }
    if (text == "seek"){
        return SEEK;
    }
    if (text == "hunt"){
        return HUNT;
    }
    if (text == "chase"){
        return CHASE;
    }
    if (text == "bark"){
        return BARK;
    }
    if (text == "cub"){
        return CUB;
    }
    if (text == "plunge"){
        return PLUNGE;
    }
    if (text == "fox"){
        return FOX;
    }
    if (text == "burrow"){
        return BURROW;
    }
    if (text == "inherit"){
        return INHERIT;
    }
    if (text == "growl"){
        return GROWL;
    }
    if (text == "show"){
        return SHOW;
    }
    if (text == "kitsune"){
        return KITSUNE;
    }
    if(text == "den"){
        return DEN;
    }
    if (text == "fluff"){
        return FLUFF;
    }
    if (text == "territory"){
        return TERRITORY;
    }
    if (text == "pack"){
        return PACK;
    }
    if (text == "guarded"){
        return GUARDED;
    }
    if (text == "vanish"){
        return VANISH;
    }
    if (text == "and"){
        return AND;
    }
    if (text == "or"){
        return OR;
    }
    if (text == "not"){
        return NOT;
    }
    if(text == "stop"){
        return STOP;
    }
    if(text == "pounce"){
        return POUNCE;
    }
    if (text == "forage"){
        return FORAGE;
    }
    return IDENTIFIER;
}

std::vector<Token> lex(std::string input){
    std::vector<Token> tokens;
    int currentPos = 0;

    while(currentPos < input.length()){
        int tokenStartPos = currentPos;
        char currChar = input[currentPos];
        if (isspace(currChar)){
            currentPos++;
        }
        else if (currChar == '+'){
            currentPos++;
            if (currentPos < input.length() && input[currentPos] == '+') {
                tokens.push_back(Token(INC, "++", tokenStartPos));
                currentPos++;  // Skip the second '+'
            } else if (currentPos < input.length() && input[currentPos] == '='){
                tokens.push_back(Token(ADD_EQ, "+=", tokenStartPos));
                currentPos++;  // Skip the '='
            } else {
                tokens.push_back(Token(ADD, "+", tokenStartPos));
            }
        }
        else if (currChar == '-'){
            currentPos++;
            if (currentPos < input.length() && input[currentPos] == '-') {
                tokens.push_back(Token(DEC, "--", tokenStartPos));
                currentPos++;  // Skip the second '-'
            } else if (currentPos < input.length() && input[currentPos] == '='){
                tokens.push_back(Token(SUB_EQ, "-=", tokenStartPos));
                currentPos++;  // Skip the '='
            } else if (currentPos < input.length() && input[currentPos] == '>'){
                tokens.push_back(Token(ARROW_OP, "->", tokenStartPos));
                currentPos++;  // Skip the '='
            } else {
                tokens.push_back(Token(SUB, "-", tokenStartPos));
            }
        }
        else if (currChar == '='){
            currentPos++;
            if (currentPos < input.length() && input[currentPos] == '=') {
                tokens.push_back(Token(EQ, "==", tokenStartPos));
                currentPos++;  // Skip the second '='
            } else {
                tokens.push_back(Token(ASSIGN_EQU, "=", tokenStartPos));
            }
        }
        else if (currChar == '^'){
             currentPos++;
            if (currentPos < input.length() && input[currentPos] == '='){
                tokens.push_back(Token(EXP_EQ, "^=", tokenStartPos));
                currentPos++;  // Skip the '='
            }
            tokens.push_back(Token(EXP, "^", tokenStartPos));
        }
        else if (currChar == '*'){
            currentPos++;
            if (currentPos < input.length() && input[currentPos] == '='){
                tokens.push_back(Token(MUL_EQ, "*=", tokenStartPos));
                currentPos++;  // Skip the '='
            }
            tokens.push_back(Token(STAR, "*", tokenStartPos));
        }
        else if (currChar == '%'){
            currentPos++;
            if (currentPos < input.length() && input[currentPos] == '='){
                tokens.push_back(Token(MOD_EQ, "%=", tokenStartPos));
                currentPos++;  // Skip the '='
            }
            tokens.push_back(Token(MOD, "*", tokenStartPos));
        }
        else if (currChar == '/'){
            currentPos++;
            if (currentPos < input.length() && input[currentPos] == '='){
                tokens.push_back(Token(DIV_EQ, "/=", tokenStartPos));
                currentPos++;  // Skip the '='
            }
            else if (currentPos < input.length() && input[currentPos] == '/'){
                currentPos++;
                while (currentPos < input.length() && input[currentPos] != '\n'){
                    currentPos++; //skip comments
                }
            }
            else{
                tokens.push_back(Token(DIV, "/", tokenStartPos));
            }
        }
        else if (currChar == '<'){
            currentPos++;
            if (currentPos < input.length() && input[currentPos] == '='){
                tokens.push_back(Token(LEQ, "<=", tokenStartPos));
                currentPos++;  // Skip the '='
            }
            tokens.push_back(Token(LT, "/", tokenStartPos));
        }
        else if (currChar == '>'){
            currentPos++;
            if (currentPos < input.length() && input[currentPos] == '='){
                tokens.push_back(Token(GEQ, ">=", tokenStartPos));
                currentPos++;  // Skip the '='
            }
            tokens.push_back(Token(GT, "/", tokenStartPos));
        }
        else if (currChar == '!'){
            currentPos++;
            if (currentPos < input.length() && input[currentPos] == '='){
                tokens.push_back(Token(NEQ, "!=", tokenStartPos));
                currentPos++;  // Skip the '='
            }
            else{
                //not operator is a the keyword 'not' like python and not an exclamation mark
                std::cerr << "Error: invalid token '!' " << tokenStartPos << std::endl;
            }
        }
        else if (currChar == '"'){
            std::string stringValue = "";
            currentPos++;
            while (currentPos < input.length() && input[currentPos] != '"'){
                // Handle escaped characters
                if (input[currentPos] == '\\' && (currentPos + 1 < input.length())) {
                    currentPos++;  // Skip the escape character
                    switch (input[currentPos]) {
                        case 'n': stringValue += '\n'; break;  // Newline
                        case 't': stringValue += '\t'; break;  // Tab
                        case '"': stringValue += '"'; break;  // Double quote
                        // Add more cases as needed
                        default: stringValue += input[currentPos]; break;  // Default to adding the character
                    }
                } else {
                    stringValue += input[currentPos];
                }
                currentPos++;
            }
            if (currentPos < input.length() && input[currentPos] == '"') {
                currentPos++;  // Skip the closing quote
                tokens.push_back(Token(STRING, stringValue, tokenStartPos));
            } else {
                // Handle error: string not closed
                std::cerr << "Error: Unclosed string literal at position " << tokenStartPos << std::endl;
                exit(-1);
            }
        }
        else if (currChar == '\''){
            char charValue = '\0';
            currentPos++;

            if (currentPos >= input.length()) {
                std::cerr << "Error: Unclosed char literal at position " << tokenStartPos << std::endl;
                exit(-1);
            }
            if (currentPos < input.length() && input[currentPos] == '\\') {
                currentPos++;  // Skip the escape character
                if (currentPos < input.length()){
                    switch (input[currentPos]) {
                        case 'n': charValue = '\n'; break;  // Newline
                        case 't': charValue = '\t'; break;  // Tab
                        case '\'': charValue = '\''; break;  // Double quote
                        // Add more cases as needed
                        default: charValue = input[currentPos]; break;  // Default to adding the character
                    }
                }
                currentPos++;
            } else if (currentPos < input.length()) {
                if(input[currentPos] !=  '\''){
                    charValue = input[currentPos];
                    currentPos++; //go to next char for checking if it is closing quote
                }
                else{
                    std::cerr << "Error: empy char at" << tokenStartPos << std::endl;
                    exit(-1);
                }
            }
            if (currentPos < input.length() && input[currentPos] == '\'') {
                currentPos++;  // Skip the closing quote
                tokens.push_back(Token(CHAR, std::string(1, charValue), tokenStartPos));
            } else {
                // Handle error: string not closed
                std::cerr << "Error: Unclosed char literal at position " << tokenStartPos << std::endl;
                exit(-1);
            }
        }
        else if (isdigit(currChar)){
            currentPos++;
            //get current char which is first digit
            std::string num = std::string(1, currChar);
            //get all digits until a non digit encountered or end of file
            while (currentPos < input.length() && isdigit(input[currentPos])){
                num += input[currentPos];
                currentPos++;
            }
            //if the digit next is a '.' then check for all the desmial points and for double or float
            if(currentPos < input.length() && input[currentPos] == '.'){
                num += input[currentPos]; //add decimal to number
                currentPos++;
                //get all the numbers after decimal
                while (currentPos < input.length() && isdigit(input[currentPos])){
                    num += input[currentPos];
                    currentPos++;
                }
                //check to see if float
                if (currentPos < input.length() && input[currentPos] == 'f'){
                    currentPos++;
                    tokens.push_back(Token(FLOAT, num, tokenStartPos));
                }
                //otherwise double
                else{
                    tokens.push_back(Token(DOUBLE, num, tokenStartPos));
                }
            } else if (currentPos < input.length() && input[currentPos] == 'f'){
                currentPos++;
                tokens.push_back(Token(FLOAT, num, tokenStartPos));
            } else{
                tokens.push_back(Token(INT, num, tokenStartPos));
            }
        }
        else if (isalpha(currChar)){
            std::string text = std::string(1, currChar);
            currentPos++;
            while(currentPos < input.length() && isalnum(input[currentPos])){
                text += input[currentPos];
                currentPos++;
            }
            TokenType tpe = proccessKeyWord(text);
            tokens.push_back(Token(tpe, text, tokenStartPos));
        }
        else if (currChar == ';'){
            currentPos++;
            tokens.push_back(Token(SEMICOLON, ";", tokenStartPos));
        }
        else if (currChar == ','){
            currentPos++;
            tokens.push_back(Token(COMMA, ",", tokenStartPos));
        }
        else if (currChar == '('){
            currentPos++;
            tokens.push_back(Token(LPAREN, "(", tokenStartPos));
        }
        else if (currChar == ')'){
            currentPos++;
            tokens.push_back(Token(RPAREN, ")", tokenStartPos));
        }
        else if (currChar == '{'){
            currentPos++;
            tokens.push_back(Token(LBRACE, "{", tokenStartPos));
        }
        else if (currChar == '}'){
            currentPos++;
            tokens.push_back(Token(RBRACE, "}", tokenStartPos));
        }
        else if (currChar == '['){
            currentPos++;
            tokens.push_back(Token(LSQ_BRACE, "[", tokenStartPos));
        }
        else if (currChar == ']'){
            currentPos++;
            tokens.push_back(Token(RSQ_BRACE, "]", tokenStartPos));
        }
        else if (currChar == EOF){
            currentPos++;
            break;
        }
        else{
            std::cerr << "Error: Unknown character " << currChar <<" at "<< tokenStartPos << std::endl;
            exit(-1);
        }

    }

    tokens.push_back(Token(END_FILE, (std::string)"<EOF>", currentPos));
    return tokens;
}

class Node;
class IntLiteralNode;
class FloatLiteralNode;
class DoubleLiteralNode;
class CharLiteralNode;
class StringLiteralNode;
class BoolLiteralNode;
class ParamterNode;
class CodeBlockNode;
class FuncDecNode;
class ExpressionNode;
class TypeCastNode;
class LogicalExpressionNode;
class logicalNotNode;
class AssignmentStatementNode;
class FuncCallStatementNode;
class ConditionStatementNode;
class ForLoopNode;
class WhileLoopNode;
class returnStatementNode;
class breakStatementNode;
enum DataType {INT_T, DOUBLE_T, FLOAT_T, CHAR_T, STRING_T, BOOL_T, VOID_T, INVALID_TYPE};
enum AssignmentOp {EQ_OP, AEQ, SEQ, MEQ, DEQ, MOEQ, EEQ, INVALID_OP};
class Visitor{
    public:
    virtual void visit(IntLiteralNode& node) = 0;
    virtual void visit(FloatLiteralNode& node) = 0;
    virtual void visit(DoubleLiteralNode& node) = 0;
    virtual void visit(CharLiteralNode& node) = 0;
    virtual void visit(StringLiteralNode& node) = 0;
    virtual void visit(BoolLiteralNode& node) = 0;
    virtual void visit(ParamterNode& node) = 0;
    virtual void visit(CodeBlockNode& node) = 0;
    virtual void visit(ExpressionNode& node) = 0;
    virtual void visit(LogicalExpressionNode& node) = 0;
    virtual void visit(TypeCastNode& node) = 0;
    virtual void visit(logicalNotNode& node) = 0;
    virtual void visit(AssignmentStatementNode& node) = 0;
    virtual void visit(FuncCallStatementNode& node) = 0;
    virtual void visit(ConditionStatementNode& node) = 0;
    virtual void visit(ForLoopNode& node) = 0;
    virtual void visit(WhileLoopNode& node) = 0;
    virtual void visit(returnStatementNode& node) = 0;
    virtual void visit(breakStatementNode& node) = 0;
};

class Node{
    public:
    virtual ~Node() = default;
    virtual void accept(Visitor& visitor) = 0;
};

class IntLiteralNode : public Node{
    public:
    int val;
    void accept(Visitor& visitor) override {}
};

class FloatLiteralNode : public Node{
    public:
    float val;
    void accept(Visitor& visitor) override {}
};

class DoubleLiteralNode : public Node{
    public:
    double val;
    void accept(Visitor& visitor) override {}
};

class CharLiteralNode : public Node{
    public:
    char val;
    void accept(Visitor& visitor) override {}
};

class StringLiteralNode : public Node{
    public:
    std::string val;
    void accept(Visitor& visitor) override {}
};

class BoolLiteralNode : public Node{
    public:
    bool val;
    void accept(Visitor& visitor) override {}
};

class ParamterNode : public Node{
    public:
    DataType type;
    std::string identifer;
    int dim;
    void accept(Visitor& visitor) override {}
};

class CodeBlockNode : public Node{
    public:
    std::vector<std::unique_ptr<Node>> statements;
    void accept(Visitor& visitor) override {}
};

class FuncDecNode : public Node{
    public:
    DataType type;
    std::vector<std::unique_ptr<ParamterNode>> params; 
    std::unique_ptr<CodeBlockNode> body;
    void accept(Visitor& visitor) override {}
};

class ExpressionNode : public Node{
    public:
    std::unique_ptr<Node> expression; //can be TypeCast or LogicalExpression node
    void accept(Visitor& visitor) override {}
};

class TypeCastNode : public Node{
    public:
        DataType type;
        std::unique_ptr<Node> expression;
        void accept(Visitor& visitor) override {}
};

class LogicalExpressionNode : public Node{
    public:
    std::unique_ptr<Node> operand1;
    std::unique_ptr<Node> operand2;
    TokenType operation;
    void accept(Visitor& visitor) override {}
};



class logicalNotNode : public Node{ //a logicalTerm that negates. otherwise the logical term is really another node
    public:
    std::unique_ptr<Node> operand1;
    void accept(Visitor& visitor) override {}
};

class AssignmentStatementNode : public Node{
    public:
    DataType type;
    std::string identifer;
    TokenType operation;
    std::unique_ptr<Node> expression;
    void accept(Visitor& visitor) override {}
};

class FuncCallStatementNode : public Node{
    public:
    std::string identifier;
    std::vector<std::unique_ptr<Node>> args;
    void accept(Visitor& visitor) override {}
};

class ConditionStatementNode : public Node{ //can be used for elif as well
    public:
    std::unique_ptr<Node> expression;
    std::unique_ptr<CodeBlockNode> block;
    std::unique_ptr<Node> elseBlock; //may also be another condition node as it can represent an elif as well
    void accept(Visitor& visitor) override {}

};

class ForLoopNode : public Node{
    public:
    std::unique_ptr<AssignmentStatementNode> assignSatement;
    std::unique_ptr<Node> condition;
    std::unique_ptr<Node> increment;
    std::unique_ptr<CodeBlockNode> block;
    void accept(Visitor& visitor) override {}
};

class WhileLoopNode : public Node{
    public:
    std::unique_ptr<Node> expresion;
    std::unique_ptr<CodeBlockNode> block;
    void accept(Visitor& visitor) override {}
};

class returnStatementNode : public Node{
    public:
    std::unique_ptr<Node> expression; //what to return
    void accept(Visitor& visitor) override {}
};

class breakStatementNode : public Node{
    public:
    std::unique_ptr<Node> expression; //how many loops to break out of
    void accept(Visitor& visitor) override {}
};

class continueStatementNode : public Node{
    public:
    void accept(Visitor& visitor) override {}
};

class RelationalExpression : public Node{
    std::unique_ptr<Node> operand1;
    std::unique_ptr<Node> operand2;
    TokenType operation;
    void accept(Visitor& visitor) override {}
};



//TODO: implement methods after parser is done
class EvalVisitor : public Visitor{
    virtual void visit(IntLiteralNode& node) {};
    virtual void visit(FloatLiteralNode& node) {};
    virtual void visit(DoubleLiteralNode& node) {};
    virtual void visit(CharLiteralNode& node) {};
    virtual void visit(StringLiteralNode& node) {};
    virtual void visit(BoolLiteralNode& node) {};
    virtual void visit(ParamterNode& node) {};
    virtual void visit(CodeBlockNode& node) {};
    virtual void visit(ExpressionNode& node) {};
    virtual void visit(LogicalExpressionNode& node) {};
    virtual void visit(TypeCastNode& node) {};
    virtual void visit(logicalNotNode& node) {};
    virtual void visit(AssignmentStatementNode& node) {};
    virtual void visit(FuncCallStatementNode& node) {};
    virtual void visit(ConditionStatementNode& node) {};
    virtual void visit(ForLoopNode& node) {};
    virtual void visit(WhileLoopNode& node) {};
    virtual void visit(returnStatementNode& node) {};
    virtual void visit(breakStatementNode& node) {};
};

class Parser{
    private:
    


    Token currentToken;
    std::vector<Token> tokens;
    int currIndex;

    Token eat(){
        Token eaten = currentToken;
        currIndex++;
        //if we went passed the last token (should be eof) then we can return it without trying to set current token
        if (currIndex > tokens.size()-1){
            return eaten;
        }
        currentToken = tokens[currIndex];
        return eaten;
    }

    Token vomit(){
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

    Token lookAhead(int a=1){
        if (tokens.size() > currIndex+a){
            return tokens[currIndex+a];
        }
        std::cerr << "Error cant look that far ahead " << currentToken.text << " " 
        << currentToken.startPos << "currIndex: "<< currIndex << "lookahead: " << a << std::endl; 
        exit(-1);
    }

    //checks for dataType specifiers like 'int'
    DataType dataDeclaration(){
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

    std::unique_ptr<ParamterNode> parameter(){
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

    std::unique_ptr<TypeCastNode> typeCast(){
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

    std::unique_ptr<Node> logicalNot(){
        bool isNot = false;
        if (currentToken == NOT){
            isNot = true;
            eat(); //eat token
        }

        //TODO: finish

    }

    std::unique_ptr<Node> logicalExpression(){
        std::unique_ptr<Node> term = logicalNot();
        if (term == nullptr){
            std::cerr << "Error: should not happen. logicalNot should return a node or have error before returning"
            << currentToken.text << currentToken.startPos << std::endl;
            exit(-1);
        }
        //if no logical expresison term pass node up
        if (currentToken != AND && currentToken != OR){ return term; }


        std::unique_ptr<LogicalExpressionNode> exp(new LogicalExpressionNode);
        exp->operand1 = std::move(term);

        //set operation to 'and' or 'or'
        exp->operation = currentToken.type;
        eat(); //eat logic operator token 

        term = logicalNot();
        if (term == nullptr){
            std::cerr << "Error: should not happen. logicalNot should return a node or have error before returning"
            << currentToken.text << currentToken.startPos << std::endl;
            exit(-1);
        }

        exp->operand2 = std::move(term);
        return exp;
        

    }

    std::unique_ptr<Node> expression(){
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

    std::unique_ptr<AssignmentStatementNode> assignStatement(){
        std::unique_ptr<AssignmentStatementNode> as;
        as->type = INVALID_TYPE; //there may be no type in statement. semantic analysis wil lreveal if there should be or not
        if (currentToken == FLUFF){
            eat(); //eat fluff token
            DataType type = dataDeclaration();
            if (type == INVALID_TYPE){ //if there is fluff then there should be valid data type
                std::cerr << "Invalid type at " << currentToken.text << " " << currentToken.startPos << std::endl;
                exit(-1);
            }
            eat(); //eat data type declaration token
            as->type = type;
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
                if (as->operation == INVALID_OP){ 
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
        if (currentToken != SEMICOLON){
            std::cerr << "Error: expected ';' at " << currentToken.text << " " << currentToken.startPos << std::endl;
            exit(-1);
        }
        return as;
    }

   std::unique_ptr<Node> statement(){
        std::unique_ptr<AssignmentStatementNode> assignStatementNode = assignStatement();
        if (assignStatementNode != nullptr){
            eat();
            return assignStatementNode;
        }
        //TODO: check for other statements
   }

    std::unique_ptr<CodeBlockNode> codeBlock(){
        if (currentToken != LBRACE){
            std::cerr << "Error: Missing opening bracket at " << currentToken.text << " " << currentToken.startPos << std::endl;
            exit(-1);
        }
        eat(); //eat opening brace
        std::unique_ptr<CodeBlockNode> block(new CodeBlockNode);
        while (currentToken != RBRACE){
            std::unique_ptr<Node> Statement = statement();
            (block->statements).push_back(std::move(Statement));
        }
        eat(); //eat closing brace
        return block;

    }

    std::unique_ptr<FuncDecNode> functionDeclaration(){
        DataType dataType = dataDeclaration();
        if (dataType == INVALID_TYPE){
            //no data type keyword found but doesnt mean invalid syntax return and try another statemnt
            return nullptr; 
        }
        eat(); //eat data type token
        if (currentToken != PLUNGE){
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
        eat(); //eat identifier token (function name)
        if (currentToken != LPAREN){
            std::cerr << "Error: invalid function defenition at " << currentToken.text << " " << currentToken.startPos << std::endl;
            exit(-1);
        }
        eat(); //eat '('
        
        std::unique_ptr<ParamterNode> param = parameter();
        std::unique_ptr<FuncDecNode> declaration(new FuncDecNode());
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

    std::unique_ptr<Node> program(){
        std::unique_ptr<FuncDecNode> funcDec = functionDeclaration();
        //TODO: check other statements
    }

    public:
    //pass token list by reference
    Parser(std::vector<Token> &tokens) {
        this->tokens = tokens;
        currIndex = 0;
        currentToken = (this->tokens)[currIndex];
    }

    std::unique_ptr<Node> parse(){
        return program();
    }
};

int main(int argc, char** argv){

    if (argc >= 2){
        std::string fileName = argv[1];
        
        std::ifstream file(fileName);

        std::string input = "";
        
        if (file.is_open()){
            while (!file.eof()){
                input += file.get(); //get every character in file
            }
            std::cout << input << std::endl;
            std::vector<Token> tokens = lex(input);
            for (int i=0; i<tokens.size(); i++){
                std::cout << "Token(" << tokens[i].type << ", " << tokens[i].text << ", " << tokens[i].startPos << ')'<< std::endl;
            }
        }
        else{
            std::cerr << "Error: invalid file " << fileName << std::endl;
        }
    }
    else{
        std::cerr << "Error: Invalid number of arguments" << std::endl; 
    }

    return 0;
}