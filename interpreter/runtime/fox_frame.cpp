
#include "fox_frame.h"


FoxFrame::FoxFrame(std::unordered_map<std::string, std::shared_ptr<Value>> locals, VirtualMachine& vm) : VM(vm){
    this->locals = locals;
}
FoxFrame::FoxFrame(std::unordered_map<std::string, std::shared_ptr<Value>> locals, std::vector<ByteCode> code, VirtualMachine& vm) : VM(vm){
    this->locals = locals;
    this->code = code;
}
FoxFrame::FoxFrame(std::unordered_map<std::string, std::shared_ptr<Value>> locals, std::vector<ByteCode> code, std::stack<std::shared_ptr<Value>> operand_stack, VirtualMachine& vm) : VM(vm){
    this->locals = locals;
    this->code = code;
    this->operand_stack = operand_stack;
}
FoxFrame::FoxFrame(std::vector<ByteCode> code, VirtualMachine& vm) : VM(vm){
    this->code = code;
}

void FoxFrame::execute(){

}
void FoxFrame::push_operand(std::shared_ptr<Value> data){
    operand_stack.push(data);
}
void FoxFrame::pop_operand(){
    operand_stack.pop();

}
void FoxFrame::set_parent(FoxFrame* parent){
    this->parent = parent;

}
void FoxFrame::set_caller(FoxFrame* caller){
    this->caller = caller;
}
void FoxFrame::return_exit(){
    if (!operand_stack.empty()){
        this->caller->push_operand(operand_stack.top());
    }
    VM.popFrame();
}
