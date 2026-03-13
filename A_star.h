//
// Created by gionimbus on 3/9/26.
//

#ifndef ASTERISM_VALIDATOR_A_STAR_H
#define ASTERISM_VALIDATOR_A_STAR_H

#include <vector>
#include "State.h"
#include "Board_set.h"

// TODO: maybe move const expressions to helper.h
constexpr int DX[] = {0, 0, 1, -1, 0};
constexpr int DY[] = {1, -1, 0, 0, 0};
constexpr int NUM_DIRECTIONS = 5;
constexpr int SCALE_FACTOR = 10;
constexpr int HEURISTIC_SCALED_WEIGHT = 12;

class A_star {
public:
    static std::vector<State> search (const State& start, State& goal);

private:
    struct State_hasher;
    struct State_comparator;

    static std::vector<int> assign_targets (const State& state);
    static void align_states (const State& start, State& goal);
    static std::vector<State> get_next_states (const State& state, const std::vector<int>& targets);
    static bool is_valid_state (const State& state, const std::vector<int>& targets);
    static int calculate_manhattan_distance_global (const State& current, const State& goal);
    static int calculate_manhattan_distance (const Position& current, const Position& goal);
    static std::vector<State> reconstruct_path (std::unordered_map<State, State, State_hasher>& came_from, State current);
};

struct A_star::State_hasher {
    std::size_t operator() (const State& state) const {
        std::size_t seed = 0;

        for (const auto& bs : state.get_pos()) {
            seed ^= std::hash<int>{}(bs.x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= std::hash<int>{}(bs.y) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }

        return seed;
    }
};

struct A_star::State_comparator {
    bool operator()(const std::pair<int, State>& a, const std::pair<int, State>& b) const {
        return a.first > b.first;
    }
};


#endif //ASTERISM_VALIDATOR_A_STAR_H