//
// Created by gionimbus on 3/9/26.
//

#ifndef ASTERISM_VALIDATOR_A_STAR_H
#define ASTERISM_VALIDATOR_A_STAR_H

#include <vector>
#include "State.h"
#include "Board_set.h"

constexpr std::array<int, 9> DX_OCTILE= {0, 0, 0, 1, -1, 1, 1, -1, -1};
constexpr std::array<int, 9> DY_OCTILE = {0, 1, -1, 0, 0, 1, -1, 1, -1};
constexpr std::array<int, 5> DX_MANHATTAN = {0, 0, 0, 1, -1};
constexpr std::array<int, 5> DY_MANHATTAN = {0, 1, -1, 0, 0};
constexpr std::array<int, 9> DX_CHEBYSHEV = DX_OCTILE;
constexpr std::array<int, 9> DY_CHEBYSHEV = DY_OCTILE;
constexpr int NUM_DIRECTIONS_MANHATTAN = DX_MANHATTAN.size();
constexpr int NUM_DIRECTIONS_OCTILE = DX_OCTILE.size();
constexpr int NUM_DIRECTIONS_CHEBYSHEV = NUM_DIRECTIONS_OCTILE;
constexpr int SCALE_FACTOR = 1000;
constexpr float HEURISTIC_WEIGHT = 20;
constexpr int ORTHOGONAL_COST = 1 * SCALE_FACTOR;
constexpr int ORTHOGONAL_COST_WEIGHTED = ORTHOGONAL_COST * HEURISTIC_WEIGHT;
constexpr int DIAGONAL_COST = 1.414 * SCALE_FACTOR;
constexpr int DIAGONAL_COST_WEIGHTED = DIAGONAL_COST * HEURISTIC_WEIGHT;
constexpr int SAFE_DISTANCE = 100; // between POMs, measured  in mm
constexpr int SAFE_DISTANCE_SQUARED = SAFE_DISTANCE * SAFE_DISTANCE;
constexpr int SEARCH_GRID_SIZE = 5; // mm

class A_star {
public:
    static std::vector<State> search_octile (const State& start, State& goal);
    static std::vector<State> search_manhattan (const State& start, State& goal);
    static std::vector<State> search_chebyshev (const State& start, State& goal);

    static std::vector<int> assign_targets (const State& state);

private:
    struct State_hasher;
    struct State_comparator;

    static inline int calculate_manhattan_distance_global (const State& current, const State& goal);
    static inline int calculate_manhattan_distance_weighted (const Position& current, const Position& goal);
    static inline int calculate_octile_distance_global (const State& current, const State& goal);
    static inline int calculate_octile_distance_weighted (const Position& current, const Position& goal);
    static inline int calculate_chebyshev_distance_global (const Position& current, const Position& goal);
    static inline int calculate_chebyshev_distance_weighted (const Position& current, const Position& goal);

    static inline int calculate_move_cost (const State& current, const State& neighbor);

    static inline bool is_valid_state (Board_set& board_set, const State& state, const std::vector<int>& targets);
    static inline std::vector<State> get_next_states_octile (Board_set& board_set, const State& state, const std::vector<int>& targets);
    static inline std::vector<State> get_next_states_manhattan (Board_set& board_set, const State& state, const std::vector<int>& targets);
    static inline std::vector<State> get_next_states_chebyshev (Board_set& board_set, const State& state, const std::vector<int>& targets);
    static void align_states (const State& start, State& goal);

    static std::vector<State> reconstruct_path (std::unordered_map<State, State, State_hasher>& came_from, State current);
};


#endif //ASTERISM_VALIDATOR_A_STAR_H