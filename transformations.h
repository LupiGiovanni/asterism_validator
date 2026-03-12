//
// Created by gionimbus on 3/12/26.
//

#ifndef ASTERISM_VALIDATOR_TRANSFORMATIONS_H
#define ASTERISM_VALIDATOR_TRANSFORMATIONS_H

#include "Asterism.h"
#include "State.h"

inline Asterism transform_into_asterism (const State& state) {
    Asterism a ( state.get_pos()[0].get_x(),
                  state.get_pos()[1].get_x(),
                 state.get_pos()[2].get_x(),
                 state.get_pos()[0].get_y(),
                  state.get_pos()[1].get_y(),
                 state.get_pos()[2].get_y() );
    return a;
}

inline State transform_into_state (const Asterism& asterism) {
    State s ( static_cast<int>(std::round(asterism.get_ngs(0).x())),
              static_cast<int>(std::round(asterism.get_ngs(1).x())),
              static_cast<int>(std::round(asterism.get_ngs(2).x())),
              static_cast<int>(std::round(asterism.get_ngs(0).y())),
              static_cast<int>(std::round(asterism.get_ngs(1).y())),
              static_cast<int>(std::round(asterism.get_ngs(2).y())) );

    return s;
}

#endif //ASTERISM_VALIDATOR_TRANSFORMATIONS_H