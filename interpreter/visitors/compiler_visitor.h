#ifndef COMPILER_H
#define COMPILER_H

#include "visitor.h"
#include "../nodes/concrete_nodes.h"
#include "../runtime/code_object.h"
#include "../runtime/values.h"
#include "../runtime/byte_codes.h"
#include <unordered_map>
#include <stack>

// NOTES FOR FUTURE IMPLEMENTATION: 
// for scope checking create a map for both variables and functions that map their names to a scope level.
// Add the name of the current function that a given varaible/function is defined in to the name of the said variable/function.
// When checking if a variable is in scope, you can check the current function and all of the parent functions (tracked by a stack)
// names plus the variable/function name ot see if it is already defined (by looking up in map). 
// But you still allow different functions to define two local variables of the same name
// by making them unique by adding that functions name. 
// scope levle value only increases by conditionals, loops, and flow control, not functions.
// maintain a vector of all the variables names so the variables names get mapped to a integer value for byte code.
// Do simular consts.

class Compiler : public Visitor{

    struct IdentifierInfo {
        int scope_level;
        int byte_code_val;
        IdentifierInfo(int sl, int bcv) : scope_level(sl), byte_code_val(bcv) {}
    };

    std::vector<std::string> function_scope; // used to track scope relationships.

    // allows us to see what scopes variables/functions are defined in and what their byte code reference is
    std::unordered_map<std::string, IdentifierInfo> variables;
    std::unordered_map<std::string, IdentifierInfo> functions;

    //what will be given the VM.
    std::vector<CodeObject*> byte_code_consts;
    std::vector<std::shared_ptr<Value>> consts;

    int current_scope_level = 0; 
    int variable_arg_reference = 0; //tracks what value to put to refer to the correct variable in scope within the byte code
    int func_arg_reference = 0;
    int consts_reference = 0;

    // used for static tpye checking. set by nodes producing values of given types, 
    //checked by nodes defening the correct type
    DataType current_type = VOID_T;

    void compileError(std::string error_msg){
        std:: cerr << error_msg << std::endl;
        for (CodeObject* code : byte_code_consts){
            delete code;
        }
        exit(-1);
    }

    public:
    std::vector<CodeObject*>& get_code() {return byte_code_consts;}
    std::vector<std::shared_ptr<Value>>& get_consts() {return consts;}

    Value visit(ProgramNode& node) override;

    Value visit(IntLiteralNode& node) override;

    Value visit(FloatLiteralNode& node) override;
    Value visit(DoubleLiteralNode& node) override;
    Value visit(CharLiteralNode& node) override;
    Value visit(StringLiteralNode& node) override;
    Value visit(BoolLiteralNode& node) override;
    Value visit(ParamterNode& node) override;

    Value visit(CodeBlockNode& node) override;

    Value visit(ExpressionNode& node) override;

    Value visit(TypeCastNode& node) override;
    Value visit(LogicalNotNode& node) override;
    Value visit(AssignmentStatementNode& node) override;
    Value visit(FuncCallStatementNode& node) override;
    Value visit(ConditionStatementNode& node) override;
    Value visit(ForLoopNode& node) override;
    Value visit(WhileLoopNode& node) override;
    Value visit(ReturnStatementNode& node) override;
    Value visit(BreakStatementNode& node) override;
    Value visit(FuncDecNode& node) override;
    Value visit(ContinueStatementNode& node) override;
    Value visit(ArrayIndexingNode& node) override;
    Value visit(ArrayGetElementNode& node) override;
    Value visit(IdentifierNode& node) override;
    Value visit(IncDecStatementNode& node) override;
    Value visit(ArrayAssignmentNode& node) override;
    Value visit(ImportStatementNode& node) override;
    Value visit(ElementAssignmentNode& node) override;
    Value visit(ArrayBlockNode& node) override;
};

#endif