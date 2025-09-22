#ifndef FOX_FRAME_H
#define FOX_FRAME_H

#include "values.h"
#include "byte_codes.h"
#include <stack>
#include <vector>
#include <unordered_map>

class FoxFrame {
    private:
    std::stack<Value> operand_stack;
    std::vector<ByteCode> code;
    std::unordered_map<std::string, Value*> locals;

    public:

    FoxFrame(std::unordered_map<std::string, Value*> locals);
    FoxFrame(std::unordered_map<std::string, Value*> locals, std::vector<ByteCode> code);
    FoxFrame(std::unordered_map<std::string, Value*> locals, std::vector<ByteCode> code, std::stack<Value> operand_stack);
    FoxFrame(std::vector<ByteCode> code);
};


#endif