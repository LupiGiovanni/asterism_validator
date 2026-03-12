//
// Created by gionimbus on 3/10/26.
//

#ifndef ASTERISM_VALIDATOR_POSITION_H
#define ASTERISM_VALIDATOR_POSITION_H

#include <iostream>

class Position {
    friend class State;
    friend class A_star;
public:
    Position (int x, int y);
    bool operator == (const Position& other) const;
    int get_x() const;
    int get_y() const;
    void print () const;

private:
    int x;
    int y;


};


#endif //ASTERISM_VALIDATOR_POSITION_H