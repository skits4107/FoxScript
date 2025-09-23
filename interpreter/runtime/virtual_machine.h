#ifndef VM_H
#define VM_H


#include "values.h"
#include "fox_frame.h"
#include <stack>

class VirtualMachine{
    private:
    std::stack<FoxFrame*> frames;

    public:

    void pushFrame(FoxFrame* frame);
    void popFrame(); 
};

#endif