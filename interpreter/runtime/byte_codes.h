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
    BINAR_EXP = 12,
    LOAD_LOCAL = 13,
    LOAD_GLOBAL = 14,
    FRAME_PUSH = 15, //VMs frame stack
    FRAME_POP = 16, //VMs frame stack
    RETURN = 17,
    CALL = 18,
    AND_LOGIC = 19,
    OR_LOGIC = 20,
    NOT_LOGIC = 21,
    TO_STR = 22,
    TO_INT = 23,
    TO_BOOL = 24,
    TO_FLOAT = 25,
    TO_DOUBLE = 26,
    TO_CHAR = 27,
    LEN = 28,
    GET_ARR_ELEMENT = 29,
    SET_ARR_ELEMENT = 30,
    SAVE_LOCAL = 31,
    SAVE_GLOBAL = 32,
    POP = 33, //frames operand stack
    DUP = 34,
    HALT = 35,
    PUSH = 36, //frames operand stack
    EXTEND_ARG = 37, // for exrtending number of bytes for byte code arguments.
};

#endif