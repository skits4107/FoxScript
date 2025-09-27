#ifndef FOX_FRAME_H
#define FOX_FRAME_H

#include "values.h"
#include "byte_codes.h"
#include "virtual_machine.h"
#include <stack>
#include <vector>
#include <unordered_map>
#include <memory>

struct FoxFrame {
    public:
    std::stack<std::shared_ptr<Value>> operand_stack;
    std::unordered_map<int, std::shared_ptr<Value>> locals;
    std::vector<ByteCode>& code;
   // FoxFrame* caller = nullptr; since frames a stack and used for function calls only, the previous one should be the caller
    int current_instruction = 0;
    FoxFrame* parent = nullptr; // doesntown parent but used to get locals accessible in parent

    FoxFrame(std::vector<ByteCode>& c) : code(c){}

};


#endif