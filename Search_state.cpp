//
// Created by gionimbus on 2/1/26.
//

#include "Search_state.h"

Search_state::Search_state(): x(0), y(0) {}

Search_state::Search_state (long x, long y): x(x), y(y) {}

void Search_state::set_board_set (Board_set* board_set_ptr) {
    this->board_set_ptr = board_set_ptr;
}

void Search_state::print_state_info() const {
    std::cout << "Search state (" << x << ", " << y << ")" << std::endl;
}

float Search_state::GoalDistanceEstimate (Search_state& goal) {
    float dx = static_cast<float>(goal.x - x);
    float dy = static_cast<float>(goal.y - y);
    return std::sqrt(dx * dx + dy * dy);
}

bool Search_state::IsGoal (Search_state& goal) {
    return (x == goal.x && y == goal.y);
}

// bool Search_state::GetSuccessors(AStarSearch<Search_state>* astarsearch, Search_state* predecessor) {
//     if (predecessor == nullptr)
//         return false;
//
//     long predecessor_x = predecessor->x;
//     long predecessor_y = predecessor->y;
//     Search_state new_state;
//     if (board_set_ptr == nullptr)
//         return false;
//     new_state.set_board_set(board_set_ptr);
//
//     for (int i = -1; i <= 1; ++i) {
//         for (int j = -1; j <= 1; ++j) {
//             if (i == 0 && j == 0) continue;
//             if ( ! (predecessor_x == x + i && predecessor_y == y + j) ) {
//                 new_state = Search_state(x + i, y + j);
//                 new_state.set_board_set(board_set_ptr);
//                 astarsearch->AddSuccessor(new_state);
//             }
//         }
//     }
//
//     return true;
// }

bool Search_state::GetSuccessors(AStarSearch<Search_state>* astarsearch, Search_state* predecessor) {
    // Controllo sicurezza puntatore e indice
    if (board_set_ptr == nullptr || board_index < 0)
        return false;

    // 1. Sincronizza la board fisica con lo stato logico (x, y) di QUESTO nodo padre
    Point current_point(static_cast<double>(x), static_cast<double>(y));
    board_set_ptr->get_board(board_index).teleport(current_point);

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;

            double next_x = static_cast<double>(x + i);
            double next_y = static_cast<double>(y + j);
            Point next_point(next_x, next_y);

            // 2. Prova a muovere la board nella posizione del vicino
            if (board_set_ptr->get_board(board_index).teleport(next_point)) {

                // 3. Se il movimento è valido (è nel range), controlla collisioni con le altre board
                if (!board_set_ptr->detect_collision()) {

                    Search_state new_state(x + i, y + j);

                    // FIX IMPORTANTE: Propaga il contesto ai figli!
                    new_state.set_board_set(board_set_ptr);
                    new_state.set_board_index(board_index);

                    astarsearch->AddSuccessor(new_state);
                }
            }

            // 4. REVERT: Riporta la board alla posizione del padre per la prossima iterazione del loop
            board_set_ptr->get_board(board_index).teleport(current_point);
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

void Search_state::set_board_index(int index) {
    board_index = index;
}

