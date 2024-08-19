#include "values.h"


 // Special getter for FuncDecNode to avoid accidental copying of pointer
FuncDecNode* Value::getFuncDec() const {
    return std::get<FuncDecNode*>(data);
}
