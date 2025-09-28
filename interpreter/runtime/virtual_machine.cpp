
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
        ByteCode current_instruction = (ByteCode)current_frame->code[instruction_pointer];

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
            case EXTEND_ARG:
                extended_arg();
                break;
            case COND_JUMP:
                conditional_jump();
                break;
            case JUMP:
                jump();
                break;
            case CALL_DEFAULT:
                call_default();
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
    int arg = get_arg();

    //Search current and parent frames for the variable. compiler ensures scope
    for (FoxFrame* frame=frames.top(); frame != nullptr; frame=frame->parent){
        if (frame->locals.find(arg) != frame->locals.end()){
            frames.top()->operand_stack.push(frame->locals[arg]);
            break;
        }
    }
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

void VirtualMachine::to_str(){
    std::shared_ptr<Value> string = std::shared_ptr<Value>(frames.top()->operand_stack.top()->to_str());
    frames.top()->operand_stack.pop();
    frames.top()->operand_stack.push(string);
}
void VirtualMachine::to_int(){
    std::shared_ptr<Value> integer = std::shared_ptr<Value>(frames.top()->operand_stack.top()->to_int());
    frames.top()->operand_stack.pop();
    frames.top()->operand_stack.push(integer);
}
void VirtualMachine::to_char(){
    std::shared_ptr<Value> c = std::shared_ptr<Value>(frames.top()->operand_stack.top()->to_char());
    frames.top()->operand_stack.pop();
    frames.top()->operand_stack.push(c);
}
void VirtualMachine::to_float(){
    std::shared_ptr<Value> flt = std::shared_ptr<Value>(frames.top()->operand_stack.top()->to_float());
    frames.top()->operand_stack.pop();
    frames.top()->operand_stack.push(flt);
}
void VirtualMachine::to_double(){
    std::shared_ptr<Value> dbl = std::shared_ptr<Value>(frames.top()->operand_stack.top()->to_double());
    frames.top()->operand_stack.pop();
    frames.top()->operand_stack.push(dbl);
}
void VirtualMachine::to_bool(){
    std::shared_ptr<Value> b = std::shared_ptr<Value>(frames.top()->operand_stack.top()->to_bool());
    frames.top()->operand_stack.pop();
    frames.top()->operand_stack.push(b);
}

void VirtualMachine::get_arr_element(){
    //compiler ensures typer safety
    std::shared_ptr<IntValue> index = std::static_pointer_cast<IntValue>(frames.top()->operand_stack.top());
    frames.top()->operand_stack.pop();

    std::shared_ptr<ArrValue> arr = std::static_pointer_cast<ArrValue>(frames.top()->operand_stack.top());
    
    std::shared_ptr<Value> val = arr->get_item(index.get());
    frames.top()->operand_stack.pop();

    frames.top()->operand_stack.push(val);
}
void VirtualMachine::set_arr_element(){
    std::shared_ptr<Value> val = frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();

    std::shared_ptr<IntValue> index = std::static_pointer_cast<IntValue>(frames.top()->operand_stack.top());
    frames.top()->operand_stack.pop();

    std::shared_ptr<ArrValue> arr = std::static_pointer_cast<ArrValue>(frames.top()->operand_stack.top());

    arr->set_item(index.get(), val);
    frames.top()->operand_stack.pop();

}

void VirtualMachine::save_var(){
     int arg = get_arg();

    //Search current and parent frames for the variable if it already exists. compiler ensures scope
    for (FoxFrame* frame=frames.top(); frame != nullptr; frame=frame->parent){
        if (frame->locals.find(arg) != frame->locals.end()){
            frame->locals[arg] = frames.top()->operand_stack.top();
            frames.top()->operand_stack.pop();
            return;
        }
    }
    // if not save it the current local as a new variable
    frames.top()->locals[arg] =  frames.top()->operand_stack.top();
    frames.top()->operand_stack.pop();
}


void VirtualMachine::extended_arg(){
    int arg = frames.top()->code[frames.top()->current_instruction+1];

    arg_mod = (arg_mod << 8) + arg;
}

void VirtualMachine::conditional_jump(){
    //compiler ensures type safety
    std::shared_ptr<BoolValue> condition = std::static_pointer_cast<BoolValue>(frames.top()->operand_stack.top());
    frames.top()->operand_stack.pop();

    if (condition->val){
        jump();
    }
}
void VirtualMachine::jump(){
    int arg = get_arg();
    frames.top()->current_instruction += (arg*2) - 2; //subtract because of the incrment in the main loop
}

void VirtualMachine::call_default(){
    int arg = get_arg();

    switch (arg)
    {
    case PAW_PRINT:
        //TODO finish built ins
        break;
    case PAW_IN:
        
        break;
    default:
        break;
    }
}

void VirtualMachine::paw_print(std::shared_ptr<StringValue> text){}
std::shared_ptr<StringValue>& VirtualMachine::paw_in(std::shared_ptr<StringValue> prmompt){}

VirtualMachine::~VirtualMachine(){
    while (!frames.empty()){
        popFrame();
    }
    for (CodeObject* code : byte_code_consts){
        delete code;
    }
}