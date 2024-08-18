#include "lexer.h"
#include <cctype>  // For isspace()

//retruns token type of keywords (true, false, plunge, fluff, int, etc) otherwise it retruns identifer
TokenType Lexer::proccessKeyWord(std::string text){
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
        return KW_CHAR;
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
    if (text == "trick"){
        return TRICK;
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
    if(text == "pounce"){
        return POUNCE;
    }
    if (text == "forage"){
        return FORAGE;
    }
    if (text == "prowl"){
        return PROWL;
    }
    return IDENTIFIER;
}

std::vector<Token> Lexer::lex(std::string input){
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
            else{
                tokens.push_back(Token(LT, "<", tokenStartPos));
            }
            //tokens.push_back(Token(LT, "<", tokenStartPos));
        }
        else if (currChar == '>'){
            currentPos++;
            if (currentPos < input.length() && input[currentPos] == '='){
                tokens.push_back(Token(GEQ, ">=", tokenStartPos));
                currentPos++;  // Skip the '='
            }
            else{
                tokens.push_back(Token(GT, ">", tokenStartPos));
            }
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
            while(currentPos < input.length() && (isalnum(input[currentPos]) || input[currentPos] == '_')){
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