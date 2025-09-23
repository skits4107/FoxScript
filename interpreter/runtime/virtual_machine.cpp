
#include "virtual_machine.h"

VirtualMachine::VirtualMachine(std::unordered_map<std::string, std::vector<ByteCode>>& compiled_code) : byte_code_consts(compiled_code){
    global_frame = new FoxFrame(compiled_code["global"]);
    pushFrame(global_frame);
}

void VirtualMachine::execute(){



    frames.top()->current_instruction += 1;
}
void VirtualMachine::pushFrame(FoxFrame* frame){
    frames.push(frame);
}
void VirtualMachine::popFrame(){
    delete frames.top();
    frames.pop();
}