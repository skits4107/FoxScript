#ifndef COMPILER_H
#define COMPILER_H

#include "visitor.h"
#include "../nodes/concrete_nodes.h"

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

#endif