#ifndef CODE_OBJ_H
#define CODE_OBJ_H

#include "byte_codes.h"
#include <vector>

struct CodeObject{
    std::vector<int8_t> code;
    std::vector<int> local_params; //used for setting function paramaters in fox frames


};

#endif