#ifndef VM_H
#define VM_H


#include "values.h"
#include "fox_frame.h"
#include "code_object.h"
#include "built_in_func_codes.h"
#include <stack>


class VirtualMachine{
    private:
    //manages scopes and tracks states.
    std::stack<FoxFrame*> frames;
    FoxFrame* global_frame;

    //for sotring all compiled byte code, to be loaded on frame creation.
    //maps function names to the correct byte code.
    //subject to minor changes for now depending on future implementations.
    std::vector<CodeObject*>&  byte_code_consts; 

    std::vector<std::shared_ptr<Value>> consts; // constant values created during compilation. things like literals.
    int arg_mod = 0; //used by the extend argument instruction to store the upper bits of an arg/

    public:

    VirtualMachine(std::vector<CodeObject*>&  compiled_code);

    void execute();
    void pushFrame(FoxFrame* frame);
    void popFrame(); 
    int get_arg();

    void bin_add();
    void bin_mul();
    void bin_div();
    void bin_sub();
    void bin_mod();
    void bin_exp();
    void less_than();
    void less_than_eq();
    void equal();
    void not_equal();
    void greater_than_eq();
    void greater_than();
    void load_var();
    void load_const();
    void return_from();
    void call();
    void and_logic();
    void or_logic();
    void not_logic();
    void to_str();
    void to_int();
    void to_char();
    void to_float();
    void to_double();
    void to_bool();
    void get_arr_element();
    void set_arr_element();
    void save_var();
    void extended_arg();
    void conditional_jump();
    void jump();
    void call_default();

    //callable default functions;
    void paw_print(std::shared_ptr<StringValue> text);
    std::shared_ptr<StringValue>& paw_in(std::shared_ptr<StringValue> prmompt);

    ~VirtualMachine();

};

#endif