//
// Created by gionimbus on 3/10/26.
//

#ifndef ASTERISM_VALIDATOR_STATE_H
#define ASTERISM_VALIDATOR_STATE_H

#include <vector>
#include "Board_state.h"

class State {
    friend class A_star;
public:
    State ();
    State (const Board_state& s0, const Board_state& s1, const Board_state& s2);
    State (long s0_x, long s1_x, long s2_x, long s0_y, long s1_y, long s2_y);
    std::vector<Board_state> get_s () const;
    bool operator == (const State& other) const;
    void print() const;

private:
    std::vector<Board_state> s;
};


#endif //ASTERISM_VALIDATOR_STATE_H