//
// Created by gionimbus on 3/9/26.
//

#ifndef ASTERISM_VALIDATOR_A_STAR_H
#define ASTERISM_VALIDATOR_A_STAR_H

#include <vector>
#include "State.h"
#include "Board_set.h"

constexpr int DX[] = {0, 0, 1, -1, 0};
constexpr int DY[] = {1, -1, 0, 0, 0};
constexpr int NUM_DIRECTIONS = 5;

class A_star {
public:
    static std::vector<State> search (const State& start, const State& goal);

private:
    struct State_hasher;
    struct State_comparator;

    static std::vector<State> get_next_states (const State& state);
    static bool is_valid_state (const State& state);
    static long calculate_manhattan_distance (const State& current, const State& goal);
    static long calculate_manhattan_distance_helper (const Board_state& current, const Board_state& goal);
    static std::vector<State> reconstruct_path (std::unordered_map<State, State, State_hasher>& came_from, State current);
};

struct A_star::State_hasher {
    std::size_t operator() (const State& state) const {
        std::size_t seed = 0;

        for (const auto& bs : state.get_s()) {
            seed ^= std::hash<long>{}(bs.x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= std::hash<long>{}(bs.y) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }

        return seed;
    }
};

struct A_star::State_comparator {
    bool operator()(const std::pair<long, State>& a, const std::pair<long, State>& b) const {
        return a.first > b.first;
    }
};


#endif //ASTERISM_VALIDATOR_A_STAR_H