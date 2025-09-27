
#include "virtual_machine.h"
#include "byte_codes.h"

VirtualMachine::VirtualMachine(std::unordered_map<std::string, std::vector<ByteCode>>& compiled_code) : byte_code_consts(compiled_code){
    global_frame = new FoxFrame(compiled_code["global"]);
    pushFrame(global_frame);
}

void VirtualMachine::execute(){
    while (frames.size() >= 1){
        
        int instruction_pointer = frames.top()->current_instruction;
        ByteCode current_instruction = frames.top()->code[instruction_pointer];

        switch(current_instruction){
            case BINARY_ADD:

                break;
            default:
                break; //nop
        }



        if (instruction_pointer < frames.top()->code.size()-1){
            frames.top()->current_instruction += 1;
        }
        else{
            popFrame();
        }
    }
}
void VirtualMachine::pushFrame(FoxFrame* frame){
    frames.push(frame);
}
void VirtualMachine::popFrame(){
    delete frames.top();
    frames.pop();
}