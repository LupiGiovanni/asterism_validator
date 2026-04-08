//
// Created by gionimbus on 3/9/26.
//

#ifndef ASTERISM_VALIDATOR_A_STAR_H
#define ASTERISM_VALIDATOR_A_STAR_H

#include <vector>
#include "Board_set.h"

typedef Asterism State;

class A_star {
public:
    static std::vector<State> search_isometric (const State& start, State& goal, auto valid_state_function);
    static std::vector<State> search_manhattan (const State& start, State& goal, auto valid_state_function);

    static bool is_valid_state (Board_set& board_set, const State& state);
    static bool is_valid_state_fov_large_excluded (Board_set& board_set, const State& state);
    static bool is_valid_state_fov_small_excluded (Board_set& board_set, const State& state);

private:
    struct State_hasher;
    struct State_comparator;

    static double euclidean_distance (const Point& current, const Point& goal);
    static double manhattan_distance (const Point& current, const Point& goal);
    static double euclidean_distance_sum (const State& current, const State& goal);
    static double manhattan_distance_sum (const State& current, const State& goal);

    static void align_states (const State& start, State& goal);
    static std::vector<State> get_next_states_isometric (Board_set& board_set, const State& state, auto valid_state_function);
    static std::vector<State> get_next_states_manhattan (Board_set& board_set, const State& state, auto valid_state_function);
    static std::vector<State> get_next_states_triangular (Board_set& board_set, const State& state, auto valid_state_function);

    static bool is_goal_reached (const State& current, const State& goal);

    static std::vector<State> reconstruct_path (std::unordered_map<State, State, State_hasher>& came_from, State current);
};

// TODO: maybe hash with long long values
struct A_star::State_hasher {
    inline std::size_t operator() (const State& state) const {
        std::size_t seed = 0;

        for (const auto& p : state.get_points()) {
            long long x = static_cast<long long>(std::round(p.x() * HASH_PRECISION_FACTOR));
            long long y = static_cast<long long>(std::round(p.y() * HASH_PRECISION_FACTOR));

            seed ^= std::hash<long long>{}(x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= std::hash<long long>{}(y) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }

        return seed;
    }
};

// TODO: maybe implement safe way to compare doubles (but will it be slower?)
struct A_star::State_comparator {
    inline bool operator() (const std::pair<double, State>& a, const std::pair<double, State>& b) const {
        return a.first > b.first;
    }
};

// TODO: implement max iteration index to prevent infinite loops
std::vector<State> A_star::search_isometric (const State& start, State& goal, auto valid_state_function) {
    std::priority_queue<std::pair<double, State>, std::vector<std::pair<double, State>>, State_comparator> open_set;
    std::unordered_map<State, State, State_hasher> came_from;
    std::unordered_map<State, double, State_hasher> g_score;

    align_states (start, goal);
    g_score[start] = 0;
    open_set.push({euclidean_distance_sum(start, goal), start});

    Board_set temporary;
    temporary.assign_targets(start);
    temporary.teleport(start);
    temporary.assign_targets(goal);

    State current;
    constexpr double cost = GRID_SIZE;
    double candidate_g;
    double f_score;
    double h;
    int states_explored = 0;

    while (!open_set.empty()) {
        current = open_set.top().second;
        open_set.pop();
        states_explored++;

        if ( is_goal_reached(current, goal) ) {
            std::cout << "A* search (isometric) explored " << states_explored << " states." << std::endl;
            return reconstruct_path(came_from, current);
        }

        for ( const auto& neighbor : get_next_states_isometric(temporary, current, valid_state_function) ) {
            candidate_g = g_score[current] + cost;

            if (g_score.find(neighbor) == g_score.end() || candidate_g < g_score[neighbor]) {
                came_from[neighbor] = current;
                g_score[neighbor] = candidate_g;

                h = euclidean_distance_sum(neighbor, goal);
                f_score = candidate_g + h;

                open_set.push({f_score, neighbor});
            }
        }
    }

    return {};
}

std::vector<State> A_star::search_manhattan (const State& start, State& goal, auto valid_state_function) {
    std::priority_queue<std::pair<double, State>, std::vector<std::pair<double, State>>, State_comparator> open_set;
    std::unordered_map<State, State, State_hasher> came_from;
    std::unordered_map<State, double, State_hasher> g_score;

    align_states (start, goal);
    g_score[start] = 0;
    open_set.push({manhattan_distance_sum(start, goal), start});

    Board_set temporary;
    temporary.assign_targets(start);
    temporary.teleport(start);
    temporary.assign_targets(goal);

    State current;
    constexpr double cost = GRID_SIZE;
    double candidate_g;
    double f_score;
    double h;

    while (!open_set.empty()) {
        current = open_set.top().second;
        open_set.pop();

        if ( is_goal_reached(current, goal) )
            return reconstruct_path(came_from, current);

        for ( const auto& neighbor : get_next_states_manhattan(temporary, current, valid_state_function) ) {
            candidate_g = g_score[current] + cost;

            if (g_score.find(neighbor) == g_score.end() || candidate_g < g_score[neighbor]) {
                came_from[neighbor] = current;
                g_score[neighbor] = candidate_g;

                h = manhattan_distance_sum(neighbor, goal);
                f_score = candidate_g + h;

                open_set.push({f_score, neighbor});
            }
        }
    }

    return {};
}

std::vector<State> A_star::get_next_states_isometric (Board_set& board_set, const State& state, auto valid_state_function) {
    State next;
    std::vector<State> next_vector;

    for (int i = 0; i < NUM_DIRECTIONS_ISOMETRIC; ++i)
        for (int j = 0; j < NUM_DIRECTIONS_ISOMETRIC; ++j)
            for (int k = 0; k < NUM_DIRECTIONS_ISOMETRIC; ++k) {
                if (i == 0 && j == 0 && k == 0)
                    continue;

                next.set_points({ Point( state[0].x() + DX_isometric[i] * GRID_SIZE, state[0].y() + DY_isometric[i] * GRID_SIZE ),
                                     Point( state[1].x() + DX_isometric[j] * GRID_SIZE, state[1].y() + DY_isometric[j] * GRID_SIZE ),
                                     Point( state[2].x() + DX_isometric[k] * GRID_SIZE, state[2].y() + DY_isometric[k] * GRID_SIZE ) });

                if ( valid_state_function(board_set, next) )
                    next_vector.push_back(next);
            }
    return next_vector;
}

std::vector<State> A_star::get_next_states_manhattan (Board_set& board_set, const State& state, auto valid_state_function) {
    State next;
    std::vector<State> next_vector;

    for (int i = 0; i < NUM_DIRECTIONS_MANHATTAN; ++i)
        for (int j = 0; j < NUM_DIRECTIONS_MANHATTAN; ++j)
            for (int k = 0; k < NUM_DIRECTIONS_MANHATTAN; ++k) {
                if (i == 0 && j == 0 && k == 0)
                    continue;

                next.set_points({ Point( state[0].x() + DX_manhattan[i] * GRID_SIZE, state[0].y() + DY_manhattan[i] * GRID_SIZE ),
                                     Point( state[1].x() + DX_manhattan[j] * GRID_SIZE, state[1].y() + DY_manhattan[j] * GRID_SIZE ),
                                     Point( state[2].x() + DX_manhattan[k] * GRID_SIZE, state[2].y() + DY_manhattan[k] * GRID_SIZE ) });

                if ( valid_state_function(board_set, next) )
                    next_vector.push_back(next);
            }
    return next_vector;
}

std::vector<State> A_star::get_next_states_triangular (Board_set& board_set, const State& state, auto valid_state_function) {
    State next;
    std::vector<State> next_vector;

    for (int i = 0; i < NUM_DIRECTIONS_TRIANGULAR; ++i)
        for (int j = 0; j < NUM_DIRECTIONS_TRIANGULAR; ++j)
            for (int k = 0; k < NUM_DIRECTIONS_TRIANGULAR; ++k) {
                if (i == 0 && j == 0 && k == 0)
                    continue;

                next.set_points({ Point( state[0].x() + DX_triangular[i] * GRID_SIZE, state[0].y() + DY_triangular[i] * GRID_SIZE ),
                                     Point( state[1].x() + DX_triangular[j] * GRID_SIZE, state[1].y() + DY_triangular[j] * GRID_SIZE ),
                                     Point( state[2].x() + DX_triangular[k] * GRID_SIZE, state[2].y() + DY_triangular[k] * GRID_SIZE ) });

                if ( valid_state_function(board_set, next) )
                    next_vector.push_back(next);
            }
    return next_vector;
}

#endif //ASTERISM_VALIDATOR_A_STAR_H