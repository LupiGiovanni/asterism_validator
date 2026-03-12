//
// Created by gionimbus on 3/10/26.
//

#ifndef ASTERISM_VALIDATOR_STATE_H
#define ASTERISM_VALIDATOR_STATE_H

#include <vector>
#include "Position.h"
#include "Asterism.h"

class State {
    friend class A_star;
    friend class Simulation;

public:
    State ();
    State (const Position& pos0, const Position& pos1, const Position& pos2);
    State (int pos0_x, int pos1_x, int pos2_x, int pos0_y, int pos1_y, int pos2_y);
    explicit State (const Asterism& asterism);
    std::vector<Position> get_positions () const;
    bool operator == (const State& other) const;
    void print() const;

private:
    std::vector<Position> pos;
};


#endif //ASTERISM_VALIDATOR_STATE_H