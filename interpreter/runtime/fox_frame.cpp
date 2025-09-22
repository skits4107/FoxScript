
#include "fox_frame.h"

FoxFrame::FoxFrame(std::unordered_map<std::string, Value*> locals){
    this->locals = locals;
}
FoxFrame::FoxFrame(std::unordered_map<std::string, Value*> locals, std::vector<ByteCode> code){
    this->locals = locals;
    this->code = code;
}
FoxFrame::FoxFrame(std::unordered_map<std::string, Value*> locals, std::vector<ByteCode> code, std::stack<Value> operand_stack){
    this->locals = locals;
    this->code = code;
    this->operand_stack = operand_stack;
}
FoxFrame::FoxFrame(std::vector<ByteCode> code){
    this->code = code;
}