//
// Created by gionimbus on 3/9/26.
//

#ifndef ASTERISM_VALIDATOR_A_STAR_H
#define ASTERISM_VALIDATOR_A_STAR_H

#include <vector>
#include "Board_set.h"
#include "helper.h"

typedef Asterism State;

class A_star {
public:
    static std::vector<State> search (const State& start, State& goal);
    static std::vector<State> search_fov_excluded (const State& start, State& goal);

private:
    struct State_hasher;
    struct State_comparator;

    static double calculate_octile_distance (const State& current, const State& goal);
    static double calculate_octile_distance (const Point& current, const Point& goal);

    static double calculate_move_cost (const State& current, const State& neighbor);

    static bool is_valid_state (Board_set& board_set, const State& state);
    static bool is_valid_state_fov_excluded (Board_set& board_set, const State& state);
    static bool is_goal_reached (const State& current, const State& goal);

    static std::vector<State> get_next_states (Board_set& board_set, const State& state);
    static std::vector<State> get_next_states_fov_excluded (Board_set& board_set, const State& state);

    static void align_states (const State& start, State& goal);

    static std::vector<State> reconstruct_path (std::unordered_map<State, State, State_hasher>& came_from, State current);
};


#endif //ASTERISM_VALIDATOR_A_STAR_H