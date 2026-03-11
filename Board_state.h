//
// Created by gionimbus on 3/10/26.
//

#ifndef ASTERISM_VALIDATOR_BOARD_STATE_H
#define ASTERISM_VALIDATOR_BOARD_STATE_H

#include <iostream>

class Board_state {
    friend class State;
    friend class A_star;
public:
    long get_x() const;
    long get_y() const;
    void print () const;

private:
    long x;
    long y;

    Board_state (long x, long y);
    bool operator == (const Board_state& other) const;
};


#endif //ASTERISM_VALIDATOR_BOARD_STATE_H