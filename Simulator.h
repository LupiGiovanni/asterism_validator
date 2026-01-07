//
// Created by gionimbus on 1/7/26.
//

#ifndef ASTERISM_VALIDATOR_SIMULATOR_H
#define ASTERISM_VALIDATOR_SIMULATOR_H

#include "Board_set.h"

class Simulator {
public:
    Board_set* boards;
    Asterism* asterism;

    Simulator (Board_set* boards, Asterism* asterism);
    Simulator ();
    void set_boards (Board_set* new_boards);
    void set_asterism (Asterism* new_asterism);
};


#endif //ASTERISM_VALIDATOR_SIMULATOR_H