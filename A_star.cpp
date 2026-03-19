//
// Created by gionimbus on 3/9/26.
//

#include "A_star.h"
#include "transformations.h"

struct A_star::State_hasher {
    std::size_t operator() (const State& state) const {
        std::size_t seed = 0;

        for (const auto& p : state.get_pos()) {
            seed ^= std::hash<int>{}(p.x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= std::hash<int>{}(p.y) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }

        return seed;
    }
};

struct A_star::State_comparator {
    bool operator() (const std::pair<int, State>& a, const std::pair<int, State>& b) const {
        return a.first > b.first;
    }
};

std::vector<State> A_star::search_octile (const State& start, State& goal) {
    Board_set temporary;
    std::priority_queue<std::pair<int, State>, std::vector<std::pair<int, State>>, State_comparator> open_set;
    std::unordered_map<State, State, State_hasher> came_from;
    std::unordered_map<State, int, State_hasher> g_score;

    align_states (start, goal);
    const std::vector<int> targets = assign_targets(goal);

    g_score[start] = 0;
    open_set.push({calculate_octile_distance_global(start, goal), start});

    while (!open_set.empty()) {
        State current = open_set.top().second;
        open_set.pop();

        if (current == goal)
            return reconstruct_path(came_from, current);

        for (const auto& neighbor : get_next_states_octile(temporary, current, targets)) {
            int move_cost = calculate_move_cost(current, neighbor);
            int tentative_g = g_score[current] + move_cost;

            if (g_score.find(neighbor) == g_score.end() || tentative_g < g_score[neighbor]) {
                came_from[neighbor] = current;
                g_score[neighbor] = tentative_g;
                int f_score = tentative_g + calculate_octile_distance_global(neighbor, goal);
                open_set.push({f_score, neighbor});
            }
        }
    }

    return {};
}

std::vector<State> A_star::search_manhattan (const State& start, State& goal) {
    Board_set temporary;
    std::priority_queue<std::pair<int, State>, std::vector<std::pair<int, State>>, State_comparator> open_set;
    std::unordered_map<State, State, State_hasher> came_from;
    std::unordered_map<State, int, State_hasher> g_score;

    align_states (start, goal);
    const std::vector<int> targets = assign_targets(goal);

    g_score[start] = 0;
    open_set.push({calculate_manhattan_distance_global(start, goal), start});

    while (!open_set.empty()) {
        State current = open_set.top().second;
        open_set.pop();

        if (current == goal)
            return reconstruct_path(came_from, current);

        for (const auto& neighbor : get_next_states_manhattan(temporary, current, targets)) {
            int move_cost = calculate_move_cost(current, neighbor);
            int tentative_g = g_score[current] + move_cost;

            if (g_score.find(neighbor) == g_score.end() || tentative_g < g_score[neighbor]) {
                came_from[neighbor] = current;
                g_score[neighbor] = tentative_g;
                int f_score = tentative_g + calculate_manhattan_distance_global(neighbor, goal);
                open_set.push({f_score, neighbor});
            }
        }
    }

    return {};
}

std::vector<int> A_star::assign_targets (const State& state) {
    Asterism asterism = transform_into_asterism (state);
    Board_set temporary;
    temporary.assign_targets(asterism);

    return temporary.get_targets();
}

void A_star::align_states (const State& start, State& goal) {
    std::vector<int> s_targets = assign_targets(start);
    std::vector<int> g_targets = assign_targets(goal);

    if (s_targets.empty() || g_targets.empty()) {
        std::cout << "Warning: attempted to run A_star::align_states but one or both of the states have no valid targets" << std::endl;
        return;
    }

    std::vector<Position> swapped_goal_pos {Position(0,0), Position(0,0), Position(0,0)};

    for (int i = 0; i < BOARDS_COUNT; i++)
        swapped_goal_pos[s_targets[i]] = goal.pos[g_targets[i]];

    goal.pos = swapped_goal_pos;
}

std::vector<State> A_star::get_next_states_octile (Board_set& board_set, const State& state, const std::vector<int>& targets) {
    State next;
    std::vector<State> next_vector;

    for (int i = 0; i < NUM_DIRECTIONS_OCTILE; ++i)
        for (int j = 0; j < NUM_DIRECTIONS_OCTILE; ++j)
            for (int k = 0; k < NUM_DIRECTIONS_OCTILE; ++k) {
                if (i == 0 && j == 0 && k == 0)
                    continue;

                //------------------------------------------------------------------------------
                // TODO: debug remove later
                std::cout << "Considering possible next state" << std::endl;
                //------------------------------------------------------------------------------

                next = { Position(state.pos[0].x + DX_OCTILE[i] * SEARCH_GRID_SIZE, state.pos[0].y + DY_OCTILE[i] * SEARCH_GRID_SIZE),
                            Position(state.pos[1].x + DX_OCTILE[j] * SEARCH_GRID_SIZE, state.pos[1].y + DY_OCTILE[j] * SEARCH_GRID_SIZE),
                            Position(state.pos[2].x + DX_OCTILE[k] * SEARCH_GRID_SIZE, state.pos[2].y + DY_OCTILE[k] * SEARCH_GRID_SIZE) };

                if (is_valid_state(board_set, next, targets)) {

                    //------------------------------------------------------------------------------
                    // TODO: debug remove later
                    std::cout << "Adding valid state to next states" << std::endl;
                    //------------------------------------------------------------------------------

                    next_vector.push_back(next);
                }
            }

    return next_vector;
}

std::vector<State> A_star::get_next_states_manhattan (Board_set& board_set, const State& state, const std::vector<int>& targets) {
    State next;
    std::vector<State> next_vector;

    for (int i = 0; i < NUM_DIRECTIONS_MANHATTAN; ++i)
        for (int j = 0; j < NUM_DIRECTIONS_MANHATTAN; ++j)
            for (int k = 0; k < NUM_DIRECTIONS_MANHATTAN; ++k) {
                if (i == 0 && j == 0 && k == 0)
                    continue;

                //------------------------------------------------------------------------------
                // TODO: debug remove later
                std::cout << "Considering possible next state" << std::endl;
                //------------------------------------------------------------------------------

                next = { Position(state.pos[0].x + DX_MANHATTAN[i] * SEARCH_GRID_SIZE, state.pos[0].y + DY_MANHATTAN[i] * SEARCH_GRID_SIZE),
                            Position(state.pos[1].x + DX_MANHATTAN[j] * SEARCH_GRID_SIZE, state.pos[1].y + DY_MANHATTAN[j] * SEARCH_GRID_SIZE),
                            Position(state.pos[2].x + DX_MANHATTAN[k] * SEARCH_GRID_SIZE, state.pos[2].y + DY_MANHATTAN[k] * SEARCH_GRID_SIZE) };

                if (is_valid_state(board_set, next, targets)) {

                    //------------------------------------------------------------------------------
                    // TODO: debug remove later
                    std::cout << "Adding valid state to next states" << std::endl;
                    //------------------------------------------------------------------------------

                    next_vector.push_back(next);
                }
            }

    return next_vector;
}

bool A_star::is_valid_state(Board_set& board_set, const State& state, const std::vector<int>& targets) {
    board_set.set_targets(targets);
    Asterism a = transform_into_asterism(state);
    if (!board_set.is_destination_in_range(a)) return false;

    board_set.teleport(a);
    return !board_set.detect_collision_buffers();
}

int A_star::calculate_manhattan_distance_global (const State& current, const State& goal) {
    int h = 0;

    for (int i = 0; i < BOARDS_COUNT; i++) {
        h += calculate_manhattan_distance_weighted (current.pos[i], goal.pos[i]);
    }

    return h;
}

int A_star::calculate_manhattan_distance_weighted (const Position& current, const Position& goal) {
    int dx = std::abs(current.x - goal.x);
    int dy = std::abs(current.y - goal.y);

    return (dx + dy) * ORTHOGONAL_COST_WEIGHTED;
}

int A_star::calculate_octile_distance_global (const State& current, const State& goal) {
    int h = 0;

    for (int i = 0; i < BOARDS_COUNT; i++) {
        h += calculate_octile_distance_weighted(current.pos[i], goal.pos[i]);
    }

    return h;
}

int A_star::calculate_octile_distance_weighted (const Position& current, const Position& goal) {
    int dx = std::abs(current.x - goal.x);
    int dy = std::abs(current.y - goal.y);

    if (dx < dy)
        return DIAGONAL_COST_WEIGHTED * dx + ORTHOGONAL_COST_WEIGHTED * (dy - dx);

    return DIAGONAL_COST_WEIGHTED * dy + ORTHOGONAL_COST_WEIGHTED * (dx - dy);
}

int A_star::calculate_move_cost(const State& current, const State& neighbor) {
    int total_cost = 0;

    for (int i = 0; i < BOARDS_COUNT; ++i) {
        int dx = (neighbor.pos[i].x > current.pos[i].x) ? neighbor.pos[i].x - current.pos[i].x : current.pos[i].x - neighbor.pos[i].x;
        int dy = (neighbor.pos[i].y > current.pos[i].y) ? neighbor.pos[i].y - current.pos[i].y : current.pos[i].y - neighbor.pos[i].y;

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

