#ifndef TOKEN_H
#define TOKEN_H

#include "token_type.cpp"
#include <iostream>

struct Token{
    TokenType type;
    std::string text;
    int startPos;

    Token();

    Token(TokenType type, std::string text, int startPos);

    bool operator==(TokenType tpe) const {
        return type == tpe;
    }

    bool operator!=(TokenType tpe) const {
        return type != tpe;
    }
};

#endif // TOKEN_H