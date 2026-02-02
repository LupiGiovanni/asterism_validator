//
// Created by gionimbus on 2/1/26.
//

#include "Search_state.h"

Search_state::Search_state(): x(0), y(0), board_set_ptr(nullptr) {}

Search_state::Search_state (long x, long y): x(x), y(y), board_set_ptr(nullptr) {}

void Search_state::print_state_info() const {
    std::cout << "Search state (" << x << ", " << y << ")" << std::endl;
}

void Search_state::set_board_set (Board_set* ptr) {
    board_set_ptr = ptr;
}

float Search_state::GoalDistanceEstimate (Search_state& goal) {
    float dx = static_cast<float>(goal.x - x);
    float dy = static_cast<float>(goal.y - y);
    return std::sqrt(dx * dx + dy * dy);
}

bool Search_state::IsGoal (Search_state& goal) {
    return (x == goal.x && y == goal.y);
}

bool Search_state::GetSuccessors(AStarSearch<Search_state>* astarsearch, Search_state* predecessor) {
    if (predecessor == nullptr || board_set_ptr == nullptr)
        return false;

    long predecessor_x = predecessor->x;
    long predecessor_y = predecessor->y;
    Search_state new_state;

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            if ( ! (predecessor_x == x + i && predecessor_y == y + j) && ! board_set_ptr->detect_collision() ) {
                new_state = Search_state(x + i, y + j);
                astarsearch->AddSuccessor(new_state);
            }
        }
    }

    return true;
}

float Search_state::GetCost(Search_state& successor) {
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            if (successor.x == x + i && successor.y == y + j) {
                if (i != 0 && j != 0) {
                    return 1.4142f;
                } else {
                    return 1.0f;
                }
            }
        }
    }
    return std::numeric_limits<float>::infinity();
}

bool Search_state::IsSameState(Search_state& rhs) {
    return (x == rhs.x && y == rhs.y);
}

size_t Search_state::Hash() {
    size_t h1 = hash<float>{}(x);
    size_t h2 = hash<float>{}(y);
    return h1 ^ ( h2 << 1 );
}

