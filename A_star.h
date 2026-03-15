//
// Created by gionimbus on 3/9/26.
//

#ifndef ASTERISM_VALIDATOR_A_STAR_H
#define ASTERISM_VALIDATOR_A_STAR_H

#include <vector>
#include "State.h"
#include "Board_set.h"

// TODO: maybe move const expressions to helper.h
constexpr int DX[] = {0, 0, 0, 1, -1, 1, 1, -1, -1};
constexpr int DY[] = {0, 1, -1, 0, 0, 1, -1, 1, -1};
constexpr int NUM_DIRECTIONS = 9;
constexpr int SCALE_FACTOR = 1000;

class A_star {
public:
    static std::vector<State> search (const State& start, State& goal);
    static std::vector<int> assign_targets (const State& state);

private:
    struct State_hasher;
    struct State_comparator;

    static int calculate_manhattan_distance_global (const State& current, const State& goal);
    static int calculate_manhattan_distance (const Position& current, const Position& goal);
    static int calculate_octile_distance_global (const State& current, const State& goal);
    static int calculate_octile_distance (const Position& current, const Position& goal);

    static bool is_valid_state (Board_set& board_set, const State& state, const std::vector<int>& targets);
    static std::vector<State> get_next_states (Board_set& board_set, const State& state, const std::vector<int>& targets);
    static void align_states (const State& start, State& goal);

    static std::vector<State> reconstruct_path (std::unordered_map<State, State, State_hasher>& came_from, State current);
};


#endif //ASTERISM_VALIDATOR_A_STAR_H