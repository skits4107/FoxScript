#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include "../tokens/token.h"

class Lexer{

    TokenType proccessKeyWord(std::string text);

public:
    
    std::vector<Token> lex(std::string input);
};

#endif