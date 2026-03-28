//
// Created by gionimbus on 3/9/26.
//

#include "A_star.h"

struct A_star::State_hasher {
    inline std::size_t operator() (const State& state) const {
        std::size_t seed = 0;

        for (const auto& p : state.get_points()) {
            seed ^= std::hash<double>{}(p.x()) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= std::hash<double>{}(p.y()) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }

        return seed;
    }
};

struct A_star::State_comparator {
    inline bool operator() (const std::pair<double, State>& a, const std::pair<double, State>& b) const {
        return a.first > b.first;
    }
};

std::vector<State> A_star::search (const State& start, State& goal) {
    std::priority_queue<std::pair<double, State>, std::vector<std::pair<double, State>>, State_comparator> open_set;
    std::unordered_map<State, State, State_hasher> came_from;
    std::unordered_map<State, double, State_hasher> g_score;

    align_states (start, goal);
    g_score[start] = 0;
    open_set.push({calculate_octile_distance(start, goal), start});

    Board_set temporary;
    temporary.assign_targets(start);
    temporary.teleport(start);
    temporary.assign_targets(goal);

    State current;
    double move_cost;
    double candidate_g;
    double f_score;

    while (!open_set.empty()) {
        current = open_set.top().second;
        open_set.pop();

        if ( is_goal_reached(current, goal) )
            return reconstruct_path(came_from, current);

        for (const auto& neighbor : get_next_states(temporary, current)) {
            move_cost = calculate_move_cost(current, neighbor);
            candidate_g = g_score[current] + move_cost;

            if (g_score.find(neighbor) == g_score.end() || candidate_g < g_score[neighbor]) {
                came_from[neighbor] = current;
                g_score[neighbor] = candidate_g;
                f_score = candidate_g + calculate_octile_distance(neighbor, goal);
                open_set.push({f_score, neighbor});
            }
        }
    }

    return {};
}

std::vector<State> A_star::search_fov_excluded (const State& start, State& goal) {
        std::priority_queue<std::pair<double, State>, std::vector<std::pair<double, State>>, State_comparator> open_set;
        std::unordered_map<State, State, State_hasher> came_from;
        std::unordered_map<State, double, State_hasher> g_score;

        align_states (start, goal);
        g_score[start] = 0;
        open_set.push({calculate_octile_distance(start, goal), start});

        Board_set temporary;
        temporary.assign_targets(goal);
        State current;
        double move_cost;
        double candidate_g;
        double f_score;

        while (!open_set.empty()) {
            current = open_set.top().second;
            open_set.pop();

            if ( is_goal_reached(current, goal) )
                return reconstruct_path(came_from, current);

            for (const auto& neighbor : get_next_states_fov_excluded(temporary, current)) {
                move_cost = calculate_move_cost(current, neighbor);
                candidate_g = g_score[current] + move_cost;

                if (g_score.find(neighbor) == g_score.end() || candidate_g < g_score[neighbor]) {
                    came_from[neighbor] = current;
                    g_score[neighbor] = candidate_g;
                    f_score = candidate_g + calculate_octile_distance(neighbor, goal);
                    open_set.push({f_score, neighbor});
                }
            }
        }

        return {};
}

void A_star::align_states (const State& start, State& goal) {
    Board_set temporary;
    temporary.assign_targets(start);
    temporary.teleport(start);
    std::vector<int> s_targets = temporary.get_targets();
    temporary.assign_targets(goal);
    std::vector<int> g_targets = temporary.get_targets();

    if (s_targets.empty() || g_targets.empty()) {
        std::cout << "Warning: attempted to run A_star::align_states but one or both of the states have no valid targets" << std::endl;
        return;
    }

    std::vector<Point> swapped_goal_pos {Point(0,0), Point(0,0), Point(0,0)};

    for (int i = 0; i < BOARDS_COUNT; i++)
        swapped_goal_pos[ s_targets[i] ] = goal[ g_targets[i] ];

    goal.set_points(swapped_goal_pos);
}

std::vector<State> A_star::get_next_states (Board_set& board_set, const State& state) {
    State next;
    std::vector<State> next_vector;

    for (int i = 0; i < NUM_DIRECTIONS; ++i)
        for (int j = 0; j < NUM_DIRECTIONS; ++j)
            for (int k = 0; k < NUM_DIRECTIONS; ++k) {
                if (i == 0 && j == 0 && k == 0)
                    continue;

                //------------------------------------------------------------------------------
                // TODO: debug remove later
                //std::cout << "Considering possible next state" << std::endl;
                //------------------------------------------------------------------------------

                next.set_points({ Point( state[0].x() + DX[i] * SEARCH_GRID_SIZE, state[0].y() + DY[i] * SEARCH_GRID_SIZE ),
                                     Point( state[1].x() + DX[j] * SEARCH_GRID_SIZE, state[1].y() + DY[j] * SEARCH_GRID_SIZE ),
                                     Point( state[2].x() + DX[k] * SEARCH_GRID_SIZE, state[2].y() + DY[k] * SEARCH_GRID_SIZE ) });

                if ( is_valid_state(board_set, next) ) {

                    //------------------------------------------------------------------------------
                    // TODO: debug remove later
                    //std::cout << "Adding valid state to next states" << std::endl;
                    //next.print();
                    //------------------------------------------------------------------------------

                    next_vector.push_back(next);
                }
            }

    return next_vector;
}

std::vector<State> A_star::get_next_states_fov_excluded (Board_set& board_set, const State& state) {
    State next;
    std::vector<State> next_vector;

    for (int i = 0; i < NUM_DIRECTIONS; ++i)
        for (int j = 0; j < NUM_DIRECTIONS; ++j)
            for (int k = 0; k < NUM_DIRECTIONS; ++k) {
                if (i == 0 && j == 0 && k == 0)
                    continue;

                next.set_points({ Point( state[0].x() + DX[i] * SEARCH_GRID_SIZE, state[0].y() + DY[i] * SEARCH_GRID_SIZE ),
                                     Point( state[1].x() + DX[j] * SEARCH_GRID_SIZE, state[1].y() + DY[j] * SEARCH_GRID_SIZE ),
                                     Point( state[2].x() + DX[k] * SEARCH_GRID_SIZE, state[2].y() + DY[k] * SEARCH_GRID_SIZE ) });

                if ( is_valid_state_fov_excluded(board_set, next) )
                    next_vector.push_back(next);
            }

    return next_vector;
}

bool A_star::is_valid_state (Board_set& board_set, const State& state) {
    if ( ! board_set.is_destination_in_range(state) )
        return false;

    board_set.teleport(state);
    return ! board_set.detect_collision_buffers();
}

bool A_star::is_valid_state_fov_excluded (Board_set& board_set, const State& state) {
    if ( ! board_set.is_destination_in_range(state) )
        return false;

    board_set.teleport(state);
    return ! board_set.detect_collision_buffers() && ! board_set.detect_vignette_fov_large();
}

bool A_star::is_goal_reached (const State& current, const State& goal) {
    for (int i = 0; i < BOARDS_COUNT; i++) {
        double dx = std::abs(current[i].x() - goal[i].x());
        double dy = std::abs(current[i].y() - goal[i].y());

        if (dx > GOAL_REACHED_TOLERANCE || dy > GOAL_REACHED_TOLERANCE)
            return false;
    }

    return true;
}

double A_star::calculate_octile_distance (const State& current, const State& goal) {
    double h = 0;

    for (int i = 0; i < BOARDS_COUNT; i++) {
        h += calculate_octile_distance(current[i], goal[i]);
    }

    return h;
}

double A_star::calculate_octile_distance (const Point& current, const Point& goal) {
    double dx = std::abs(current.x() - goal.x());
    double dy = std::abs(current.y() - goal.y());

    if (dx < dy)
        return DIAGONAL_COST * HEURISTIC_WEIGHT * dx + ORTHOGONAL_COST * HEURISTIC_WEIGHT * (dy - dx);

    return DIAGONAL_COST * HEURISTIC_WEIGHT * dy + ORTHOGONAL_COST * HEURISTIC_WEIGHT * (dx - dy);
}

double A_star::calculate_move_cost (const State& current, const State& neighbor) {
    double total_cost = 0;

    for (int i = 0; i < BOARDS_COUNT; ++i) {
        double dx = (neighbor[i].x() > current[i].x()) ? neighbor[i].x() - current[i].x() : current[i].x() - neighbor[i].x();
        double dy = (neighbor[i].y() > current[i].y()) ? neighbor[i].y() - current[i].y() : current[i].y() - neighbor[i].y();

        if (dx == 0 && dy == 0)
            continue;

        if (dx != 0 && dy != 0)
            total_cost += DIAGONAL_COST;
        else
            total_cost += ORTHOGONAL_COST;
    }
    return total_cost;
}

std::vector<State> A_star::reconstruct_path (std::unordered_map<State, State, State_hasher>& came_from, State current) {
    std::vector<State> total_path = {current};

    while (came_from.find(current) != came_from.end()) {
        current = came_from[current];
        total_path.push_back(current);
    }

    std::reverse(total_path.begin(), total_path.end());

    return total_path;
}

