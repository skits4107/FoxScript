#ifndef NODE_H
#define NODE_H

#include "../forward_declarations.h"
#include "../runtime/values.h"

class Node{
    public:
    virtual ~Node() = default;
    virtual Value accept(Visitor& visitor) = 0;
};

#endif