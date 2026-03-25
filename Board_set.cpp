//
// Created by gionimbus on 12/30/25.
//

#include "Board_set.h"

Board_set::Board_set(): boards{Board(Board_type::type0), Board(Board_type::type1), Board(Board_type::type2)}, targets{} {
    fov_large.push_back(CAD_coordinates::R);
    fov_large.push_back(CAD_coordinates::S);
    fov_large.push_back(CAD_coordinates::T);
    fov_large.push_back(CAD_coordinates::U);

    fov_small.push_back(CAD_coordinates::V);
    fov_small.push_back(CAD_coordinates::W);
    fov_small.push_back(CAD_coordinates::X);
    fov_small.push_back(CAD_coordinates::Y);

    constexpr double technical_field_radius_squared = TECHNICAL_FIELD_RADIUS * TECHNICAL_FIELD_RADIUS;
    technical_field = Circle(Point(0., 0.), technical_field_radius_squared);

    // Note that we do not need to rotate fov_small, fov_large and technical field because they are already aligned
    // with our reference system
}

const std::vector<Board>& Board_set::get_boards() const {
    return boards;
}

std::vector<int> Board_set::get_targets() const {
    return targets;
}

bool Board_set::detect_collision() const {
    if ( CGAL::do_intersect(boards[0].profile, boards[1].profile) ||
         CGAL::do_intersect(boards[1].profile, boards[2].profile) ||
         CGAL::do_intersect(boards[0].profile, boards[2].profile) )
        return true;

    return false;
}

bool Board_set::detect_vignette_fov_small() const {
    for (const auto& board : boards)
        if (CGAL::do_intersect(board.profile, fov_small))
            return true;

    return false;
}

bool Board_set::detect_vignette_fov_large() const {
    for (const auto& board : boards)
        if (CGAL::do_intersect(board.profile, fov_large))
            return true;

    return false;
}

double Board_set::calculate_distance (const Asterism& destination_asterism) const {
    double distance = std::numeric_limits<double>::infinity();

    if (targets.size() == BOARDS_COUNT) {
        distance = 0;
        for (int i = 0; i < BOARDS_COUNT; i++)
            distance += boards[i].calculate_distance(destination_asterism[ targets[i] ]);
    }
    else if (targets.empty())
        std::cout << "Warning: attempted to run Board_set::calculate_distance but 'targets' field is empty" << std::endl;

    else
        std::cout << "Warning: attempted to run Board_set::calculate_distance but 'targets' field has size != 3" << std::endl;

    return distance;
}

// TODO: maybe optimize also by minimization of maximum span (i.e. the maximum time any board needs to reach its target)
void Board_set::assign_targets (const Asterism& destination_asterism) {
    Board_set temporary;
    targets.clear();

    const int permutations_count = 6;
    const std::vector<std::vector<int>> permutations = {
        {0, 1, 2},
        {0, 2, 1},
        {1, 0, 2},
        {1, 2, 0},
        {2, 0, 1},
        {2, 1, 0}
    };

    std::vector< std::pair< std::vector<int>, double > > target_distance_vector;

    for (int i = 0; i < permutations_count; i++)
            if ( temporary.boards[0].teleport( destination_asterism[ permutations[i][0] ] ) &&
                 temporary.boards[1].teleport( destination_asterism[ permutations[i][1] ] ) &&
                 temporary.boards[2].teleport( destination_asterism[ permutations[i][2] ] ) &&
                 ! temporary.detect_collision() )
                {
                temporary.targets = permutations[i];
                target_distance_vector.push_back( std::make_pair( permutations[i], temporary.calculate_distance( destination_asterism ) ) );
                }

    if (target_distance_vector.empty())
        targets = {};
    else {
        auto min_element = std::ranges::min_element(target_distance_vector,
            [](const std::pair< std::vector<int>, double >& a, const std::pair< std::vector<int>, double >& b) { return a.second < b.second; });

        targets = min_element->first;
    }
}

void Board_set::set_targets (const std::vector<int>& new_targets) {
    if (new_targets.size() == BOARDS_COUNT || new_targets.empty())
        targets = new_targets;
    else
        std::cout << "Warning: attempted to run Board_set::set_targets but 'new_targets' vector has size != 3" << std::endl;
}

void Board_set::teleport (const Asterism& destination_asterism) {
    if (targets.empty())
        std::cout << "Warning: attempted to run Board_set::teleport but 'targets' field is empty" << std::endl;

    else if (targets.size() != BOARDS_COUNT)
        std::cout << "Warning: attempted to run Board_set::teleport but 'targets' field has size != 3" << std::endl;

    else
        for (int j = 0; j < BOARDS_COUNT; j++)
            boards[j].teleport(destination_asterism[ targets[j] ]);
}

bool Board_set::is_destination_in_range (const Asterism& destination_asterism) const {
    if (targets.empty())
        std::cout << "Warning: attempted to run Board_set::is_destination_in_range but 'targets' field is empty" << std::endl;

    else if (targets.size() != BOARDS_COUNT)
        std::cout << "Warning: attempted to run Board_set::is_destination_in_range but 'targets' field has size != 3" << std::endl;

    else
        for (int j = 0; j < BOARDS_COUNT; j++)
            if ( ! boards[j].is_in_range( destination_asterism[targets[j]] ) )
                return false;

    return true;
}

bool Board_set::is_destination_reached (const Asterism& destination_asterism, double tolerance) const {
    if (targets.empty())
        std::cout << "Warning: attempted to run Board_set::is_destination_reached but 'targets' field is empty" << std::endl;

    else if (targets.size() != BOARDS_COUNT)
        std::cout << "Warning: attempted to run Board_set::is_destination_reached but 'targets' field has size != 3" << std::endl;

    else
        for (int j = 0; j < BOARDS_COUNT; j++)
            if ( ! boards[j].is_destination_reached(destination_asterism[ targets[j] ], tolerance) )
                return false;

    return true;
}

bool Board_set::is_destination_aligned_x (const Asterism& destination_asterism) const {
    for (int j = 0; j < BOARDS_COUNT; j++)
        if ( ! boards[j].is_destination_aligned_x(destination_asterism[ targets[j] ]) )
            return false;

    return true;
}

bool Board_set::is_destination_aligned_y (const Asterism& destination_asterism) const {
    for (int j = 0; j < BOARDS_COUNT; j++)
        if ( ! boards[j].is_destination_aligned_y(destination_asterism[ targets[j] ]) )
            return false;

    return true;
}

bool Board_set::is_in_technical_field () const {
    for (int j = 0; j < BOARDS_COUNT; j++)
        if ( boards[j].is_in_technical_field(technical_field) )
            return true;

    return false;
}

bool Board_set::is_in_safe_zone () const {
    for (int j = 0; j < BOARDS_COUNT; j++)
        if ( ! boards[j].is_in_safe_zone() )
            return false;

    return true;
}

bool Board_set::move (const Asterism& destination_asterism, double distance_step) {
    if (targets.empty())
        std::cout << "Warning: attempted to run Board_set::move but 'targets' field is empty" << std::endl;

    else if (targets.size() != BOARDS_COUNT)
        std::cout << "Warning: attempted to run Board_set::move but 'targets' field has size != 3" << std::endl;

    else
        for (int j = 0; j < BOARDS_COUNT; j++)
            boards[j].move(destination_asterism[ targets[j] ], distance_step);

    return detect_collision();
}

bool Board_set::move_outside_tech_field (double distance_step) {
    for (int j = 0; j < BOARDS_COUNT; j++)
        boards[j].move_outside_tech_field(technical_field, distance_step);

    return detect_collision();
}

bool Board_set::move_to_safe_zone (double distance_step) {
    for (int j = 0; j < BOARDS_COUNT; j++)
        boards[j].move_to_safe_zone(distance_step);

    return detect_collision();
}

bool Board_set::move_along_x (const Asterism& destination_asterism, double distance_step) {
    if (targets.empty()) {
        std::cout << "Warning: attempted to run Board_set::move_along_x but 'targets' field is empty" << std::endl;
        return false;
    }

    for (int j = 0; j < BOARDS_COUNT; j++)
        boards[j].move_along_x(destination_asterism[ targets[j] ], distance_step);

    return detect_collision();
}

bool Board_set::move_along_y (const Asterism& destination_asterism, double distance_step) {
    if (targets.empty()) {
        std::cout << "Warning: attempted to run Board_set::move_along_y but 'targets' field is empty" << std::endl;
        return false;
    }

    for (int j = 0; j < BOARDS_COUNT; j++)
        boards[j].move_along_y(destination_asterism[ targets[j] ], distance_step);

    return detect_collision();
}

bool Board_set::detect_collision_buffers () const {
    if ( CGAL::do_intersect(boards[0].profile_buffer_zone, boards[1].profile_buffer_zone) ||
         CGAL::do_intersect(boards[1].profile_buffer_zone, boards[2].profile_buffer_zone) ||
         CGAL::do_intersect(boards[0].profile_buffer_zone, boards[2].profile_buffer_zone) )
        return true;

    return false;
}