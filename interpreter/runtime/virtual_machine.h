#ifndef VM_H
#define VM_H


#include "values.h"
#include "fox_frame.h"
#include "code_obj.h"
#include <stack>


class VirtualMachine{
    private:
    //manages scopes and tracks states.
    std::stack<FoxFrame*> frames;
    FoxFrame* global_frame;

    //for sotring all compiled byte code, to be loaded on frame creation or function creation.
    //maps function names to the correct byte code.
    //subject to minor changes for now depending on future implementations.
    std::unordered_map<std::string, CodeObj*>& byte_code_consts; 

    public:

    VirtualMachine(std::unordered_map<std::string, CodeObj*>& compiled_code);

    void execute();
    void pushFrame(FoxFrame* frame);
    void popFrame(); 
};

#endif