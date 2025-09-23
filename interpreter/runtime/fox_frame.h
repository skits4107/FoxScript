#ifndef FOX_FRAME_H
#define FOX_FRAME_H

#include "values.h"
#include "byte_codes.h"
#include "virtual_machine.h"
#include <stack>
#include <vector>
#include <unordered_map>
#include <memory>

class FoxFrame {
    private:
    std::stack<std::shared_ptr<Value>> operand_stack;
    std::vector<ByteCode> code;
    std::unordered_map<std::string,std::shared_ptr<Value>> locals;
    FoxFrame* parent = nullptr;
    FoxFrame* caller = nullptr;
    VirtualMachine& VM;

    public:

    FoxFrame(std::unordered_map<std::string, std::shared_ptr<Value>> locals, VirtualMachine& vm);
    FoxFrame(std::unordered_map<std::string, std::shared_ptr<Value>> locals, std::vector<ByteCode> code, VirtualMachine& vm);
    FoxFrame(std::unordered_map<std::string, std::shared_ptr<Value>> locals, std::vector<ByteCode> code, std::stack<std::shared_ptr<Value>> operand_stack, VirtualMachine& vm);
    FoxFrame(std::vector<ByteCode> code, VirtualMachine& vm);

    void execute();
    void push_operand(std::shared_ptr<Value> data);
    void pop_operand();
    void set_parent(FoxFrame* parent);
    void set_caller(FoxFrame* caller);
    void return_exit();

};


#endif