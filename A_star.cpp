//
// Created by gionimbus on 3/9/26.
//

#include "A_star.h"

std::vector<State> A_star::search(const State& start, const State& goal) {
    std::priority_queue<std::pair<long, State>, std::vector<std::pair<long, State>>, State_comparator> open_set;
    std::unordered_map<State, State, State_hasher> came_from;
    std::unordered_map<State, long, State_hasher> g_score;

    g_score[start] = 0;
    open_set.push({calculate_manhattan_distance(start, goal), start});

    while (!open_set.empty()) {
        State current = open_set.top().second;
        open_set.pop();

        if (current == goal) {
            return reconstruct_path(came_from, current);
        }

        for (const auto& neighbor : get_next_states(current)) {
            long tentative_g = g_score[current] + 1;

            if (g_score.find(neighbor) == g_score.end() || tentative_g < g_score[neighbor]) {
                came_from[neighbor] = current;
                g_score[neighbor] = tentative_g;
                long f_score = tentative_g + 2 * calculate_manhattan_distance(neighbor, goal);
                open_set.push({f_score, neighbor});
            }
        }
    }

    return {};
}

std::vector<State> A_star::get_next_states (const State& state) {
    std::vector<State> next_vector;

    for (int i = 0; i < NUM_DIRECTIONS; ++i)
        for (int j = 0; j < NUM_DIRECTIONS; ++j)
            for (int k = 0; k < NUM_DIRECTIONS; ++k) {
                if (i == 4 && j == 4 && k == 4)
                    continue;

                // TODO: debug remove later
                std::cout << "Considering possible next state" << std::endl;

                State next ( Board_state(state.s[0].x + DX[i], state.s[0].y + DY[i]),
                             Board_state(state.s[1].x + DX[j], state.s[1].y + DY[j]),
                             Board_state(state.s[2].x + DX[k], state.s[2].y + DY[k]) );

                if (is_valid_state(next)) {
                    // TODO: debug remove later
                    std::cout << "Adding valid state to next states" << std::endl;

                    next_vector.push_back(next);
                }
            }

    return next_vector;
}

bool A_star::is_valid_state (const State& state) {
    Board_set temporary;

    // TODO: debug remove later
    std::cout << "Checking validity of state: ";
    state.print();

    Asterism a ({Point(state.s[0].x, state.s[0].y), Point(state.s[1].x, state.s[1].y), Point(state.s[2].x, state.s[2].y)});
    temporary.assign_targets(a);

    return ! temporary.get_targets().empty();
}

long A_star::calculate_manhattan_distance (const State& current, const State& goal) {
    long h = 0;

    for (int i = 0; i < BOARDS_COUNT; i++) {
        long new_h = calculate_manhattan_distance_helper (current.s[i], goal.s[i]);
        if (new_h > h)
            h = new_h;
    }

    return h;
}

long A_star::calculate_manhattan_distance_helper (const Board_state& current, const Board_state& goal) {
    long dx = std::abs(current.x - goal.x);
    long dy = std::abs(current.y - goal.y);

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

