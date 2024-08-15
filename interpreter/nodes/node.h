#ifndef NODE_H
#define NODE_H

#include "../forward_declarations.h"

class Node{
    public:
    virtual ~Node() = default;
    virtual void accept(Visitor& visitor) = 0;
};

#endif