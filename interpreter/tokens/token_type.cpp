#pragma once

enum TokenType {
    // Literals
    INT, FLOAT, STRING, CHAR, DOUBLE,

    // Keywords
    SNIFF, WHIMPER, HUNT, CHASE, BARK, TRUE, FALSE, CUB, TRICK, FOX, 
    BURROW, INHERIT, GROWL, SHOW, KITSUNE,
    DEN, FLUFF, TERRITORY, PACK, GUARDED, POUNCE, FORAGE, PROWL,

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