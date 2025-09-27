#ifndef CODE_OBJ_H
#define CODE_OBJ_H

#include "byte_codes.h"
#include <vector>
#include <string>

// so compiled code for functions can contain paramter names for initalizing locals for function call frames
struct CodeObj{
    std::vector<ByteCode>& code;
    std::vector<std::string>& locals;

    CodeObj(std::vector<ByteCode>& c, std::vector<std::string>& l) : code(c), locals(l) {}
};

#endif