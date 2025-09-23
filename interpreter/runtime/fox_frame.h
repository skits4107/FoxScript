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
    std::vector<ByteCode>& code;
    std::unordered_map<std::string,std::shared_ptr<Value>> locals;
    FoxFrame* parent = nullptr;
    FoxFrame* caller = nullptr;
    int current_instruction = 0;

    FoxFrame(std::vector<ByteCode>& c) : code(c){}

};


#endif