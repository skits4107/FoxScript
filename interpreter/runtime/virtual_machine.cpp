
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

void VirtualMachine::execute(){}
void VirtualMachine::pushFrame(FoxFrame* frame){}
void VirtualMachine::popFrame(){}
void VirtualMachine::bin_add(){}
void VirtualMachine::bin_mul(){}
void VirtualMachine::bin_div(){}
void VirtualMachine::bin_sub(){}
void VirtualMachine::bin_mod(){}
void VirtualMachine::bin_exp(){}
void VirtualMachine::less_than(){}
void VirtualMachine::less_than_eq(){}
void VirtualMachine::equal(){}
void VirtualMachine::not_equal(){}
void VirtualMachine::greater_than_eq(){}
void VirtualMachine::greater_than(){}
void VirtualMachine::load_local(){}
void VirtualMachine::load_global(){}
void VirtualMachine::return_from(){}
void VirtualMachine::call(){}
void VirtualMachine::and_logic(){}
void VirtualMachine::or_logic(){}
void VirtualMachine::not_logic(){}
void VirtualMachine::to_str(){}
void VirtualMachine::to_int(){}
void VirtualMachine::to_char(){}
void VirtualMachine::to_float(){}
void VirtualMachine::to_double(){}
void VirtualMachine::to_bool(){}
void VirtualMachine::len(){}
void VirtualMachine::get_arr_element(){}
void VirtualMachine::set_arr_element(){}
void VirtualMachine::save_local(){}
void VirtualMachine::save_global(){}
void VirtualMachine::push(){}
void VirtualMachine::pop(){}
void VirtualMachine::halt(){}
void VirtualMachine::dup(){}
void VirtualMachine::extended_arg(){}
void VirtualMachine::conditional_jump(){}
void VirtualMachine::jump(){}
