//
// Created by gionimbus on 2/1/26.
//

#ifndef ASTERISM_VALIDATOR_SEARCH_STATE_H
#define ASTERISM_VALIDATOR_SEARCH_STATE_H

#include "Board_set.h"
#include "stlastar.h"
#include <cmath>

class Search_state {
    friend class AStarSearch<Search_state>;
    friend class Trajectory_generator;
private:
    Search_state();
    Search_state (long x, long y);
    void print_state_info () const;
    void set_board_set (Board_set* ptr);


    float GoalDistanceEstimate (Search_state& goal);
    bool IsGoal (Search_state& goal);
    bool GetSuccessors (AStarSearch<Search_state>* astarsearch, Search_state* predecessor);
    float GetCost (Search_state& successor);
    bool IsSameState (Search_state& rhs);
    size_t Hash();

    long x;
    long y;
    Board_set* board_set_ptr;
};

#endif //ASTERISM_VALIDATOR_SEARCH_STATE_H