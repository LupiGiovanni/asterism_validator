//
// Created by gionimbus on 3/9/26.
//

#include "A_star.h"

std::vector<State> A_star::search(const State& start, State& goal) {
    std::priority_queue<std::pair<int, State>, std::vector<std::pair<int, State>>, State_comparator> open_set;
    std::unordered_map<State, State, State_hasher> came_from;
    std::unordered_map<State, int, State_hasher> g_score;

    align_states (start, goal);
    const std::vector<int> targets = assign_targets(goal);

    g_score[start] = 0;
    open_set.push({calculate_manhattan_distance(start, goal), start});

    while (!open_set.empty()) {
        State current = open_set.top().second;
        open_set.pop();

        if (current == goal) {
            return reconstruct_path(came_from, current);
        }

        for (const auto& neighbor : get_next_states(current, targets)) {
            int tentative_g = g_score[current] + 1 * SCALE_FACTOR;

            if (g_score.find(neighbor) == g_score.end() || tentative_g < g_score[neighbor]) {
                came_from[neighbor] = current;
                g_score[neighbor] = tentative_g;
                int f_score = tentative_g + HEURISTIC_SCALED_WEIGHT * calculate_manhattan_distance(neighbor, goal);
                open_set.push({f_score, neighbor});
            }
        }
    }

    return {};
}

std::vector<int> A_star::assign_targets (const State& state) {
    Asterism goal_asterism (state.pos[0].x, state.pos[1].x, state.pos[2].x, state.pos[0].y, state.pos[1].y, state.pos[2].y);
    Board_set temporary;
    temporary.assign_targets(goal_asterism);
    return temporary.get_targets();
}

void A_star::align_states (const State& start, State& goal) {
    std::vector<int> s_tar = assign_targets(start);
    std::vector<int> g_tar = assign_targets(goal);

    if (s_tar.empty() || g_tar.empty()) {
        std::cout << "Warning: attempted to align states but one or both of the states have empty 'targets' vector" << std::endl;
        return;
    }

    std::vector<Position> swapped_goal_pos {Position(0,0), Position(0,0), Position(0,0)};

    for (int i = 0; i < BOARDS_COUNT; i++) {
        swapped_goal_pos[s_tar[i]] = goal.pos[g_tar[i]];
    }

    goal.pos = swapped_goal_pos;
}

std::vector<State> A_star::get_next_states (const State& state, const std::vector<int>& targets) {
    std::vector<State> next_vector;

    for (int i = 0; i < NUM_DIRECTIONS; ++i)
        for (int j = 0; j < NUM_DIRECTIONS; ++j)
            for (int k = 0; k < NUM_DIRECTIONS; ++k) {
                if (i == 4 && j == 4 && k == 4)
                    continue;

                // TODO: debug remove later
                std::cout << "Considering possible next state" << std::endl;

                State next ( Position(state.pos[0].x + DX[i], state.pos[0].y + DY[i]),
                             Position(state.pos[1].x + DX[j], state.pos[1].y + DY[j]),
                             Position(state.pos[2].x + DX[k], state.pos[2].y + DY[k]) );

                if (is_valid_state(next, targets)) {
                    // TODO: debug remove later
                    std::cout << "Adding valid state to next states" << std::endl;

                    next_vector.push_back(next);
                }
            }

    return next_vector;
}

bool A_star::is_valid_state (const State& state, const std::vector<int>& targets) {
    if (targets.size() != BOARDS_COUNT) {
        std::cout << "Warning: attempted to check validity of state but 'fixed_targets' vector has size != 3" << std::endl;
        return false;
    }

    Board_set temporary;

    // TODO: debug remove later
    std::cout << "Checking validity of state: ";
    state.print();

    Asterism a (state.pos[0].x, state.pos[1].x, state.pos[2].x, state.pos[0].y, state.pos[1].y, state.pos[2].y);
    temporary.set_targets(targets);
    temporary.teleport(a);

    return !temporary.detect_collision() && temporary.is_in_range(a);
}

int A_star::calculate_manhattan_distance (const State& current, const State& goal) {
    int h = 0;

    for (int i = 0; i < BOARDS_COUNT; i++) {
        int new_h = calculate_manhattan_distance_helper (current.pos[i], goal.pos[i]);
        if (new_h > h)
            h = new_h;
    }

    return h;
}

int A_star::calculate_manhattan_distance_helper (const Position& current, const Position& goal) {
    int dx = std::abs(current.x - goal.x);
    int dy = std::abs(current.y - goal.y);

    return dx + dy;
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

