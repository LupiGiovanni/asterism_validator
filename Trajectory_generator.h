//
// Created by gionimbus on 2/2/26.
//

#ifndef ASTERISM_VALIDATOR_TRAJECTORY_GENERATOR_H
#define ASTERISM_VALIDATOR_TRAJECTORY_GENERATOR_H

#include "helper.h"
#include "Board.h"
#include "Board_set.h"
#include "Search_state.h"

class Trajectory_generator {
public:
    explicit Trajectory_generator (const Board_set& board_set);

    bool generate_trajectory (const Board& board, const Point& start, const Point& goal);

    std::vector<Point> get_trajectory() const;

private:
    const Board_set& board_set;
    std::vector<Search_state> path;
    std::vector<Point> trajectory;

    bool find_path (int board_index, const Search_state& start_state, const Search_state& goal_state);
};


#endif //ASTERISM_VALIDATOR_TRAJECTORY_GENERATOR_H