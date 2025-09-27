
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
                bin_add();
                break;
            case BINARY_SUB:
                bin_sub();
                break;
            case BINARY_MUL:
                bin_mul();
                break;
            case BINARY_DIV:
                bin_div();
                break;
            case BINARY_MOD:
                bin_mod();
                break;
            case BINARY_EXP:
                bin_exp();
                break;
            case LESS_THAN:
                less_than();
                break;
            case LESS_THAN_EQUAL:
                less_than_eq();
                break;
            case EQUAL:
                equal();
                break;
            case NOT_EQUAL:
                not_equal();
                break;
            case GREATER_THAN_EQUAL:
                greater_than_eq();
                break;
            case GREATER_THAN:
                greater_than();
                break;
            case LOAD_VAR:
                load_var();
                break;
            case LOAD_CONST:
                load_const();
                break;
            case RETURN:
                return_from();
                break;
            case CALL:
                call();
                break;
            case AND_LOGIC:
                and_logic();
                break;
            case OR_LOGIC:
                or_logic();
                break;
            case NOT_LOGIC:
                not_logic();
                break;
            case TO_STR:
                to_str();
                break;
            case TO_INT:
                to_int();
                break;
            case TO_FLOAT:
                to_float();
                break;
            case TO_DOUBLE:
                to_double();
                break;
            case TO_CHAR:
                to_char();
                break;
            case TO_BOOL:
                to_bool();
                break;
            case GET_ARR_ELEMENT:
                get_arr_element();
                break;
            case SET_ARR_ELEMENT:
                set_arr_element();
                break;   
            case SAVE_VAR:
                save_var();
                break;
            case PUSH:
                push();
                break;
            case POP:
                pop();
                break;
            case HALT:
                halt();
                break;
            case EXTEND_ARG:
                extended_arg();
                break;
            case COND_JUMP:
                conditional_jump();
                break;
            case JUMP:
                jump();
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

void VirtualMachine::load_var(){}
void VirtualMachine::load_const(){}

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

void VirtualMachine::get_arr_element(){}
void VirtualMachine::set_arr_element(){}

void VirtualMachine::save_var(){}

void VirtualMachine::push(){}
void VirtualMachine::pop(){}
void VirtualMachine::halt(){}

void VirtualMachine::extended_arg(){}

void VirtualMachine::conditional_jump(){}
void VirtualMachine::jump(){}
