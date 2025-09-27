#ifndef VM_H
#define VM_H


#include "values.h"
#include "fox_frame.h"
#include <stack>


class VirtualMachine{
    private:
    //manages scopes and tracks states.
    std::stack<FoxFrame*> frames;
    FoxFrame* global_frame;

    //for sotring all compiled byte code, to be loaded on frame creation or function creation.
    //maps function names to the correct byte code.
    //subject to minor changes for now depending on future implementations.
    std::unordered_map<std::string, std::vector<ByteCode>>& byte_code_consts; 
    std::unordered_map<std::string, std::shared_ptr<Value>> variables;

    public:

    VirtualMachine(std::unordered_map<std::string, std::vector<ByteCode>>& compiled_code);

    void execute();
    void pushFrame(FoxFrame* frame);
    void popFrame(); 
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
    void load_local();
    void load_global();
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
    void len();
    void get_arr_element();
    void set_arr_element();
    void save_local();
    void save_global();
    void push();
    void pop();
    void halt();
    void dup();
    void extended_arg();

};

#endif