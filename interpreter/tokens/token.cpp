#include "token.h"

Token::Token(){
    type = END_FILE;
    text = "<EOF>";
    startPos = 0;
}

Token::Token(TokenType type, std::string text, int startPos){
    this->type = type;
    this->text = text;
    this->startPos = startPos;
}

