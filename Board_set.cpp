//
// Created by gionimbus on 12/30/25.
//

#include "Board_set.h"

Board_set::Board_set(): boards{Board(Board_type::type0), Board(Board_type::type1), Board(Board_type::type2)}, targets{} {
    fov_large.push_back(coordinates::R);
    fov_large.push_back(coordinates::S);
    fov_large.push_back(coordinates::T);
    fov_large.push_back(coordinates::U);

    fov_small.push_back(coordinates::V);
    fov_small.push_back(coordinates::W);
    fov_small.push_back(coordinates::X);
    fov_small.push_back(coordinates::Y);

    // Technical field definition
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
    if (CGAL::do_intersect(boards[0].profile, boards[1].profile) || CGAL::do_intersect(boards[1].profile, boards[2].profile)
        || CGAL::do_intersect(boards[0].profile, boards[2].profile))
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

double Board_set::calculate_distance(const Asterism& destination_asterism) const {
    double distance = 0.;

    if (targets.size() == BOARDS_COUNT) {
        for (int i = 0; i < BOARDS_COUNT; i++)
            distance += boards[i].calculate_distance(destination_asterism.get_ngs(targets[i]));
    }
    else if (targets.empty()) {
        distance = std::numeric_limits<double>::infinity();
        std::cout << "Warning: attempted to calculate distance but 'targets' vector is empty" << std::endl;
    }
    else {
        distance = std::numeric_limits<double>::infinity();
        std::cout << "Warning: attempted to calculate distance but 'targets' vector has size != 3" << std::endl;
    }

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
            if ( temporary.boards[0].teleport( destination_asterism.get_ngs( permutations[i][0] ) ) &&
                 temporary.boards[1].teleport( destination_asterism.get_ngs( permutations[i][1] ) ) &&
                 temporary.boards[2].teleport( destination_asterism.get_ngs( permutations[i][2] ) ) &&
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

void Board_set::teleport (const Asterism& destination_asterism) {
    if (targets.empty()) {
        std::cout << "Warning: attempted to teleport boards but 'targets' vector is empty" << std::endl;
    }
    else {
        for (int j = 0; j < BOARDS_COUNT; j++)
            boards[j].teleport(destination_asterism.get_ngs(targets[j]));
    }
}

bool Board_set::is_destination_reached (const Asterism &destination_asterism) const {
    for (int j = 0; j < BOARDS_COUNT; j++)
        if ( ! boards[j].is_destination_reached(destination_asterism.get_ngs(targets[j])) )
            return false;

    return true;
}

bool Board_set::is_in_technical_field () const {
    for (int j = 0; j < BOARDS_COUNT; j++)
        if ( boards[j].is_in_technical_field(technical_field) )
            return true;

    return false;
}

bool Board_set::move (const Asterism& destination_asterism, double distance_step) {
    if (targets.empty()) {
        std::cout << "Warning: attempted to move board set but 'targets' field is empty" << std::endl;
        return false;
    }

    for (int j = 0; j < BOARDS_COUNT; j++)
        boards[j].move(destination_asterism.get_ngs(targets[j]), distance_step);

    return detect_collision();
}

bool Board_set::move_outside_tech_field (double distance_step) {
    for (int j = 0; j < BOARDS_COUNT; j++)
        boards[j].move_outside_tech_field(technical_field, distance_step);

    return detect_collision();
}