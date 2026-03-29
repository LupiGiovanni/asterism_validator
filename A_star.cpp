//
// Created by gionimbus on 3/9/26.
//

#include "A_star.h"

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

bool A_star::is_valid_state (Board_set& board_set, const State& state) {
    if ( ! board_set.is_destination_in_range(state) )
        return false;

    board_set.teleport(state);
    return ! board_set.detect_collision_buffers();
}

bool A_star::is_valid_state_fov_large_excluded (Board_set& board_set, const State& state) {
    if ( ! board_set.is_destination_in_range(state) )
        return false;

    board_set.teleport(state);
    return ! board_set.detect_collision_buffers() && ! board_set.detect_vignette_fov_large();
}

bool A_star::is_valid_state_fov_small_excluded (Board_set& board_set, const State& state) {
    if ( ! board_set.is_destination_in_range(state) )
        return false;

    board_set.teleport(state);
    return ! board_set.detect_collision_buffers() && ! board_set.detect_vignette_fov_small();
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

double A_star::octile_distance (const State& current, const State& goal) {
    double h = 0;
    for (int i = 0; i < BOARDS_COUNT; i++) {
        h += octile_distance_helper(current[i], goal[i]);
    }

    return h;
}

double A_star::manhattan_distance (const State& current, const State& goal) {
    double h = 0;
    for (int i = 0; i < BOARDS_COUNT; i++) {
        h += manhattan_distance_helper(current[i], goal[i]);
    }

    return h;
}

double A_star::octile_distance_helper (const Point& current, const Point& goal) {
    double dx = std::abs(current.x() - goal.x());
    double dy = std::abs(current.y() - goal.y());

    if (dx < dy)
        return DIAGONAL_COST * HEURISTIC_WEIGHT * dx + ORTHOGONAL_COST * HEURISTIC_WEIGHT * (dy - dx);

    return DIAGONAL_COST * HEURISTIC_WEIGHT * dy + ORTHOGONAL_COST * HEURISTIC_WEIGHT * (dx - dy);
}

double A_star::manhattan_distance_helper (const Point& current, const Point& goal) {
    double dx = std::abs(current.x() - goal.x());
    double dy = std::abs(current.y() - goal.y());

    return (dx + dy) * HEURISTIC_WEIGHT * ORTHOGONAL_COST;
}

double A_star::move_cost (const State& current, const State& neighbor) {
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