//
// Created by gionimbus on 3/9/26.
//

#ifndef ASTERISM_VALIDATOR_NODE_H
#define ASTERISM_VALIDATOR_NODE_H


class Node {
    friend class A_star;
private:
    unsigned long x;
    unsigned long y;

    Node ();
    Node (unsigned long x, unsigned long y);
};


#endif //ASTERISM_VALIDATOR_NODE_H