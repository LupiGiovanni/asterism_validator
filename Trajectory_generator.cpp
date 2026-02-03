//
// Created by gionimbus on 2/2/26.
//

#include "Trajectory_generator.h"

Trajectory_generator::Trajectory_generator(const Board_set& board_set): board_set{board_set}, path{}, trajectory{} {}

bool Trajectory_generator::find_path (int board_index, const Search_state& start, const Search_state& goal) {
    AStarSearch<Search_state> search;
    unsigned int search_progress;

    Search_state start_state = start;
    Search_state goal_state = goal;
    Board_set temporary = board_set;

    start_state.set_board_set(&temporary);
    start_state.set_board_index(board_index);

    goal_state.set_board_set(&temporary);
    goal_state.set_board_index(board_index);

    search.SetStartAndGoalStates(start_state, goal_state);

    Point start_point ( static_cast<double>(start_state.x), static_cast<double>(start_state.y) );
    temporary.get_board(board_index).teleport(start_point);

    do {
        search_progress = search.SearchStep();

        // Accedere alla OpenList SOLO se la ricerca è ancora in corso.
        // Se ha finito (successo o fallimento), la lista è vuota e current_node sarebbe NULL.
        if (search_progress == AStarSearch<Search_state>::SEARCH_STATE_SEARCHING) {
            Search_state* current_node = search.GetOpenListStart();

            // Controllo di sicurezza aggiuntivo
            if (current_node != nullptr) {
                Point next(static_cast<double>(current_node->x), static_cast<double>(current_node->y));
                temporary.get_board(board_index).teleport(next);
            }
        }

    } while (search_progress == AStarSearch<Search_state>::SEARCH_STATE_SEARCHING);

    if (search_progress == AStarSearch<Search_state>::SEARCH_STATE_SUCCEEDED) {
        Search_state* state = search.GetSolutionStart();
        while (state != nullptr) {
            path.push_back(*state);
            state = search.GetSolutionNext();
        }
        search.FreeSolutionNodes();
        return true;
    }
    else if (search_progress == AStarSearch<Search_state>::SEARCH_STATE_FAILED) {
        std::cout << "Warning: path search failed" << std::endl;
        search.FreeSolutionNodes(); // È buona norma chiamarlo anche qui
    }

    return false;
}

bool Trajectory_generator::generate_trajectory (int board_index, const Point& start, const Point& goal) {
    path.clear();
    trajectory.clear();

    Search_state start_state (static_cast<long>(start.x()), static_cast<long>(start.y()));
    Search_state goal_state (static_cast<long>(goal.x()), static_cast<long>(goal.y()));

    if ( find_path(board_index, start_state, goal_state) ) {
        for (const auto& state : path) {
            trajectory.push_back( Point( static_cast<double>(state.x), static_cast<double>(state.y) ) );
        }
        return true;
    }

    return false;
}

std::vector<Point> Trajectory_generator::get_trajectory() const {
    return trajectory;
}