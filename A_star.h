//
// Created by gionimbus on 3/9/26.
//

#ifndef ASTERISM_VALIDATOR_A_STAR_H
#define ASTERISM_VALIDATOR_A_STAR_H

#include <vector>
#include "State.h"
#include "Board_set.h"
#include "helper.h"

class A_star {
public:
    static std::vector<State> search_octile (const State& start, State& goal);
    static std::vector<State> search_manhattan (const State& start, State& goal);
    static std::vector<State> search_euclidean (const State& start, State& goal);
    static std::vector<State> search_debug (const State& start, State& goal);

    static std::vector<int> assign_targets (const State& state);

private:
    struct State_hasher;
    struct State_comparator;

    static inline int calculate_manhattan_distance_global (const State& current, const State& goal);
    static inline int calculate_manhattan_distance_weighted (const Position& current, const Position& goal);
    static inline int calculate_octile_distance_global (const State& current, const State& goal);
    static inline int calculate_octile_distance_weighted (const Position& current, const Position& goal);
    static inline int calculate_euclidean_distance_global (const State& current, const State& goal);
    static inline int calculate_euclidean_distance_weighted (const Position& current, const Position& goal);

    static inline int calculate_move_cost (const State& current, const State& neighbor);

    static inline bool is_valid_state (Board_set& board_set, const State& state, const std::vector<int>& targets);
    static inline std::vector<State> get_next_states_octile (Board_set& board_set, const State& state, const std::vector<int>& targets);
    static inline std::vector<State> get_next_states_manhattan (Board_set& board_set, const State& state, const std::vector<int>& targets);
    static inline std::vector<State> get_next_states_euclidean (Board_set& board_set, const State& state, const std::vector<int>& targets);
    static void align_states (const State& start, State& goal);

    static std::vector<State> reconstruct_path (std::unordered_map<State, State, State_hasher>& came_from, State current);
};


#endif //ASTERISM_VALIDATOR_A_STAR_H