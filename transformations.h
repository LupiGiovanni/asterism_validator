//
// Created by gionimbus on 3/12/26.
//

#ifndef ASTERISM_VALIDATOR_TRANSFORMATIONS_H
#define ASTERISM_VALIDATOR_TRANSFORMATIONS_H

#include "Asterism.h"
#include "A_star.h"
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

inline State transform_into_state(const Asterism& asterism, int search_grid_size = SEARCH_GRID_SIZE) {
    if (search_grid_size <= 0) {
        std::cout << "Warning: attempted to run transform_into_state but grid size is <= 0" << std::endl;
        return State (0, 0, 0, 0, 0, 0);
    }

    auto round_to_grid = [search_grid_size](double val) -> int {
        return static_cast<int>(std::round(val / static_cast<double>(search_grid_size))) * search_grid_size;
    };

    return State(
        round_to_grid(asterism.get_ngs(0).x()),
        round_to_grid(asterism.get_ngs(1).x()),
        round_to_grid(asterism.get_ngs(2).x()),
        round_to_grid(asterism.get_ngs(0).y()),
        round_to_grid(asterism.get_ngs(1).y()),
        round_to_grid(asterism.get_ngs(2).y())
    );
}


#endif //ASTERISM_VALIDATOR_TRANSFORMATIONS_H