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
    // static std::vector<State> search_debug (const State& start, State& goal);

    // TODO: make it private ? is it necessary ?
    static std::vector<int> assign_targets (const State& state);

private:
    struct State_hasher;
    struct State_comparator;

    static inline double calculate_octile_distance_weighted_global (const State& current, const State& goal);
    static inline double calculate_octile_distance_weighted (const Point& current, const Point& goal);

    static inline double calculate_move_cost (const State& current, const State& neighbor);

    static inline bool is_valid_state (Board_set& board_set, const State& state, const std::vector<int>& targets);
    static inline bool is_goal_reached (const State& current, const State& goal);
    static inline std::vector<State> get_next_states (Board_set& board_set, const State& state, const std::vector<int>& targets);

    static void align_states (const State& start, State& goal);

    static std::vector<State> reconstruct_path (std::unordered_map<State, State, State_hasher>& came_from, State current);
};


#endif //ASTERISM_VALIDATOR_A_STAR_H