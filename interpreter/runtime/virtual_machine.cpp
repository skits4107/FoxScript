
#include "virtual_machine.h"
#include "byte_codes.h"

VirtualMachine::VirtualMachine(std::vector<CodeObject*>& compiled_code) : byte_code_consts(compiled_code){
    global_frame = new FoxFrame(compiled_code[0]->code);
    pushFrame(global_frame);
}

void VirtualMachine::execute(){
    while (frames.size() >= 1){
        
        FoxFrame* current_frame = frames.top();

        int instruction_pointer = current_frame->current_instruction;
        ByteCode current_instruction = current_frame->code[instruction_pointer];

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


        if (instruction_pointer < current_frame->code.size()-1){
            current_frame->current_instruction += 2; //2 because each isntruction is 2 bytes
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

int VirtualMachine::get_arg(){
    int arg = frames.top()->code[frames.top()->current_instruction+1]; //current instruction points to op code. plus 1 is arg.
    int arg = (arg_mod << 8) + arg; //incase of extended arg
    arg_mod = 0; //reset now that we have the full argument
    return arg;
}

void VirtualMachine::bin_add(){
    //get the two operands from frame stack
    std::shared_ptr<Value> operand1 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();
    std::shared_ptr<Value> operand2 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();

    //store result in a new shared pointer. value functions dont modifer or take owner ship so get isfine.
    std::shared_ptr<Value> result = std::shared_ptr<Value>(operand1->add(operand2.get()));
    frames.top()->operand_stack.push(result);
}
void VirtualMachine::bin_mul(){
     //get the two operands from frame stack
    std::shared_ptr<Value> operand1 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();
    std::shared_ptr<Value> operand2 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();

    //store result in a new shared pointer. value functions dont modifer or take owner ship so get isfine.
    std::shared_ptr<Value> result = std::shared_ptr<Value>(operand1->mul(operand2.get()));
    frames.top()->operand_stack.push(result);
}
void VirtualMachine::bin_div(){
     //get the two operands from frame stack
    std::shared_ptr<Value> operand1 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();
    std::shared_ptr<Value> operand2 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();

    //store result in a new shared pointer. value functions dont modifer or take owner ship so get isfine.
    std::shared_ptr<Value> result = std::shared_ptr<Value>(operand1->div(operand2.get()));
    frames.top()->operand_stack.push(result);
}
void VirtualMachine::bin_sub(){
     //get the two operands from frame stack
    std::shared_ptr<Value> operand1 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();
    std::shared_ptr<Value> operand2 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();

    //store result in a new shared pointer. value functions dont modifer or take owner ship so get isfine.
    std::shared_ptr<Value> result = std::shared_ptr<Value>(operand1->sub(operand2.get()));
    frames.top()->operand_stack.push(result);
}
void VirtualMachine::bin_mod(){
     //get the two operands from frame stack
    std::shared_ptr<Value> operand1 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();
    std::shared_ptr<Value> operand2 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();

    //store result in a new shared pointer. value functions dont modifer or take owner ship so get isfine.
    std::shared_ptr<Value> result = std::shared_ptr<Value>(operand1->mod(operand2.get()));
    frames.top()->operand_stack.push(result);
}
void VirtualMachine::bin_exp(){
     //get the two operands from frame stack
    std::shared_ptr<Value> operand1 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();
    std::shared_ptr<Value> operand2 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();

    //store result in a new shared pointer. value functions dont modifer or take owner ship so get isfine.
    std::shared_ptr<Value> result = std::shared_ptr<Value>(operand1->exp(operand2.get()));
    frames.top()->operand_stack.push(result);
}

void VirtualMachine::less_than(){
     //get the two operands from frame stack
    std::shared_ptr<Value> operand1 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();
    std::shared_ptr<Value> operand2 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();

    //store result in a new shared pointer. value functions dont modifer or take owner ship so get isfine.
    std::shared_ptr<Value> result = std::shared_ptr<Value>(operand1->lt_op(operand2.get()));
    frames.top()->operand_stack.push(result);
}
void VirtualMachine::less_than_eq(){
     //get the two operands from frame stack
    std::shared_ptr<Value> operand1 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();
    std::shared_ptr<Value> operand2 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();

    //store result in a new shared pointer. value functions dont modifer or take owner ship so get isfine.
    std::shared_ptr<Value> result = std::shared_ptr<Value>(operand1->leq_op(operand2.get()));
    frames.top()->operand_stack.push(result);
}
void VirtualMachine::equal(){
     //get the two operands from frame stack
    std::shared_ptr<Value> operand1 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();
    std::shared_ptr<Value> operand2 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();

    //store result in a new shared pointer. value functions dont modifer or take owner ship so get isfine.
    std::shared_ptr<Value> result = std::shared_ptr<Value>(operand1->eq_op(operand2.get()));
    frames.top()->operand_stack.push(result);
}
void VirtualMachine::not_equal(){
     //get the two operands from frame stack
    std::shared_ptr<Value> operand1 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();
    std::shared_ptr<Value> operand2 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();

    //store result in a new shared pointer. value functions dont modifer or take owner ship so get isfine.
    std::shared_ptr<Value> result = std::shared_ptr<Value>(operand1->neq_op(operand2.get()));
    frames.top()->operand_stack.push(result);
}
void VirtualMachine::greater_than_eq(){
     //get the two operands from frame stack
    std::shared_ptr<Value> operand1 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();
    std::shared_ptr<Value> operand2 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();

    //store result in a new shared pointer. value functions dont modifer or take owner ship so get isfine.
    std::shared_ptr<Value> result = std::shared_ptr<Value>(operand1->geq_op(operand2.get()));
    frames.top()->operand_stack.push(result);
}
void VirtualMachine::greater_than(){
     //get the two operands from frame stack
    std::shared_ptr<Value> operand1 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();
    std::shared_ptr<Value> operand2 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();

    //store result in a new shared pointer. value functions dont modifer or take owner ship so get isfine.
    std::shared_ptr<Value> result = std::shared_ptr<Value>(operand1->gt_op(operand2.get()));
    frames.top()->operand_stack.push(result);
}

void VirtualMachine::load_var(){

}
void VirtualMachine::load_const(){
    int arg = get_arg();

    frames.top()->operand_stack.push(consts[arg]);

}

void VirtualMachine::return_from(){
    std::shared_ptr<Value> to_return = frames.top()->operand_stack.top();
    popFrame();

    //put the return value on the callers operand stack
    frames.top()->operand_stack.push(to_return);
}
void VirtualMachine::call(){
    int arg = get_arg();
    CodeObject* codeObj = byte_code_consts[arg];
    FoxFrame* new_frame = new FoxFrame(codeObj->code);
    
    //NOTE: byte code needs to enter paramas backward onto operand stack
    for (int param : codeObj->local_params){
        new_frame->locals[param] = frames.top()->operand_stack.top();
    }
    pushFrame(new_frame);
}

void VirtualMachine::and_logic(){
     //get the two operands from frame stack
    std::shared_ptr<Value> operand1 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();
    std::shared_ptr<Value> operand2 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();

    //store result in a new shared pointer. value functions dont modifer or take owner ship so get isfine.
    std::shared_ptr<Value> result = std::shared_ptr<Value>(operand1->and_op(operand2.get()));
    frames.top()->operand_stack.push(result);
}
void VirtualMachine::or_logic(){
     //get the two operands from frame stack
    std::shared_ptr<Value> operand1 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();
    std::shared_ptr<Value> operand2 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();

    //store result in a new shared pointer. value functions dont modifer or take owner ship so get isfine.
    std::shared_ptr<Value> result = std::shared_ptr<Value>(operand1->or_op(operand2.get()));
    frames.top()->operand_stack.push(result);
}
void VirtualMachine::not_logic(){
    std::shared_ptr<Value> operand1 = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();

     std::shared_ptr<Value> result = std::shared_ptr<Value>(operand1->not_op());
    frames.top()->operand_stack.push(result);
}

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
