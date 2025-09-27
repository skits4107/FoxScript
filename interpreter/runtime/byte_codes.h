#ifndef BYTE_CODES_H
#define BYTE_CODES_H

#include <cstdint> // for uint8_t

enum ByteCode : uint8_t {
    BINARY_ADD = 0,
    BINARY_MUL = 1,
    BINARY_DIV = 3,
    BINARY_MOD  = 4,
    LESS_THAN = 5,
    LESS_THAN_EQUAL = 6,
    EQUAL = 7,
    NOT_EQUAL = 8,
    GREATER_THAN_EQUAL = 9,
    GREATER_THAN = 10,
    BINARY_SUB = 11,
    BINARY_EXP = 12,
    LOAD_VAR = 13,
    LOAD_CONST = 14,
    RETURN = 15,
    CALL = 16,
    AND_LOGIC = 17,
    OR_LOGIC = 18,
    NOT_LOGIC = 19,
    TO_STR = 20,
    TO_INT = 21,
    TO_BOOL = 22,
    TO_FLOAT = 23,
    TO_DOUBLE = 24,
    TO_CHAR = 25,
    GET_ARR_ELEMENT = 26,
    SET_ARR_ELEMENT = 27,
    SAVE_VAR = 28,
    POP = 29, //frames operand stack
    HALT = 30,
    PUSH = 31, //frames operand stack
    EXTEND_ARG = 32, // for exrtending number of bytes for byte code arguments.
    COND_JUMP = 33,
    JUMP = 34,
};

#endif