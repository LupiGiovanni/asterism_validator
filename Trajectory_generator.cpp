//
// Created by gionimbus on 2/2/26.
//

#include "Trajectory_generator.h"

Trajectory_generator::Trajectory_generator(const Board_set& board_set): board_set{board_set}, path{}, trajectory{} {}

bool Trajectory_generator::find_path (int board_index, const Search_state& start_state, const Search_state& goal_state) {
    AStarSearch<Search_state> search;
    unsigned int search_progress;

    Search_state start = start_state;
    Search_state goal = goal_state;
    Board_set temporary = board_set;
    start.set_board_set(&temporary);
    goal.set_board_set(&temporary);
    search.SetStartAndGoalStates(start, goal);

    do {
        search_progress = search.SearchStep();
        temporary.get_board(board_index).move
    }
    while (search_progress == AStarSearch<Search_state>::SEARCH_STATE_SEARCHING);

    if (search_progress == AStarSearch<Search_state>::SEARCH_STATE_SUCCEEDED) {
        //Saves the path to the goal
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
        search.FreeSolutionNodes();
    }

    return false;
}

bool Trajectory_generator::generate_trajectory (const Board& board, const Point& start, const Point& goal) {
    path.clear();
    trajectory.clear();

    Search_state start_state (static_cast<long>(start.x()), static_cast<long>(start.y()));
    Search_state goal_state (static_cast<long>(goal.x()), static_cast<long>(goal.y()));

    if ( find_path(board, start_state, goal_state) ) {
        for (const auto& state : path) {
            trajectory.push_back( Point( static_cast<double>(state.x), static_cast<double>(state.y) ) );
        }
        return true;
    }

    return false;
}