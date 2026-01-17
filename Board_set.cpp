//
// Created by gionimbus on 12/30/25.
//

#include "Board_set.h"

// For a graphical reference of the coordinates below see attached documentation
Board_set::Board_set(): board1(Board_type::type1), board2(Board_type::type2),board3(Board_type::type3), targets(Board_set_targets::none) {

    // Small fov coordinates
    Point R(-87.847500, -87.847500);
    Point S(87.847500, -87.847500);
    Point T(87.847500, 87.847500);
    Point U(-87.847500, 87.847500);

    fov_small.push_back(R);
    fov_small.push_back(S);
    fov_small.push_back(T);
    fov_small.push_back(U);

    // Large fov coordinates
    Point V(-33.150000, -33.150000);
    Point W(33.150000, -33.150000);
    Point X(33.150000, 33.150000);
    Point Y(-33.150000, 33.150000);

    fov_large.push_back(V);
    fov_large.push_back(W);
    fov_large.push_back(X);
    fov_large.push_back(Y);

    // Technical field definition
    constexpr double technical_field_radius = 265.2; // mm
    constexpr double technical_field_radius_squared = technical_field_radius * technical_field_radius;
    technical_field = Circle(Point(0., 0.), technical_field_radius_squared);

    // Note that we do not need to rotate fov_small and fov_large because they are already aligned with our
    // reference system
}

bool Board_set::detect_collision() const {
    bool detected = true;

    if (!CGAL::do_intersect(board1.profile, board2.profile) && !CGAL::do_intersect(board1.profile, board3.profile) && !CGAL::do_intersect(board2.profile, board3.profile))
        detected = false;

    return detected;
}

bool Board_set::detect_vignette_fov_small() const {
    bool detected = true;

    if (!CGAL::do_intersect(board1.profile, fov_small) && !CGAL::do_intersect(board2.profile, fov_small) && !CGAL::do_intersect(board3.profile, fov_small))
        detected = false;

    return detected;
}

bool Board_set::detect_vignette_fov_large() const {
    bool detected = true;

    if (!CGAL::do_intersect(board1.profile, fov_large) && !CGAL::do_intersect(board2.profile, fov_large) && !CGAL::do_intersect(board3.profile, fov_large))
        detected = false;

    return detected;
}

void Board_set::assign_targets (const Asterism& destination_asterism) {
    Board_set temporary;
    std::vector<std::pair<Board_set_targets, double>> target_distance_vector;

    if (temporary.board1.teleport(destination_asterism.ngs1) && temporary.board2.teleport(destination_asterism.ngs2) && temporary.board3.teleport(destination_asterism.ngs3) && !temporary.detect_collision()) {
        temporary.targets = Board_set_targets::ngs_123;
        target_distance_vector.push_back(std::make_pair(Board_set_targets::ngs_123, temporary.calculate_distance(destination_asterism)));
    }

    if (temporary.board1.teleport(destination_asterism.ngs1) && temporary.board2.teleport(destination_asterism.ngs3) && temporary.board3.teleport(destination_asterism.ngs2) && !temporary.detect_collision()) {
        temporary.targets = Board_set_targets::ngs_132;
        target_distance_vector.push_back(std::make_pair(Board_set_targets::ngs_132, temporary.calculate_distance(destination_asterism)));
    }

    if (temporary.board1.teleport(destination_asterism.ngs2) && temporary.board2.teleport(destination_asterism.ngs1) && temporary.board3.teleport(destination_asterism.ngs3) && !temporary.detect_collision()) {
        temporary.targets = Board_set_targets::ngs_213;
        target_distance_vector.push_back(std::make_pair(Board_set_targets::ngs_213, temporary.calculate_distance(destination_asterism)));
    }

    if (temporary.board1.teleport(destination_asterism.ngs2) && temporary.board2.teleport(destination_asterism.ngs3) && temporary.board3.teleport(destination_asterism.ngs1) && !temporary.detect_collision()) {
        temporary.targets = Board_set_targets::ngs_231;
        target_distance_vector.push_back(std::make_pair(Board_set_targets::ngs_231, temporary.calculate_distance(destination_asterism)));
    }

    if (temporary.board1.teleport(destination_asterism.ngs3) && temporary.board2.teleport(destination_asterism.ngs1) && temporary.board3.teleport(destination_asterism.ngs2) && !temporary.detect_collision()) {
        temporary.targets = Board_set_targets::ngs_312;
        target_distance_vector.push_back(std::make_pair(Board_set_targets::ngs_312, temporary.calculate_distance(destination_asterism)));
    }

    if (temporary.board1.teleport(destination_asterism.ngs3) && temporary.board2.teleport(destination_asterism.ngs2) && temporary.board3.teleport(destination_asterism.ngs1) && !temporary.detect_collision()) {
        temporary.targets = Board_set_targets::ngs_321;
        target_distance_vector.push_back(std::make_pair(Board_set_targets::ngs_321, temporary.calculate_distance(destination_asterism)));
    }

    if (target_distance_vector.empty())
        targets = Board_set_targets::none;
    else {
        auto min_element_it = std::min_element(target_distance_vector.begin(), target_distance_vector.end(), [](const std::pair<Board_set_targets, double>& a, const std::pair<Board_set_targets, double>& b) { return a.second < b.second; });
        targets = min_element_it->first;
    }
}

void Board_set::teleport (const Asterism& destination_asterism) {
    if (targets == Board_set_targets::ngs_123) {
        board1.teleport(destination_asterism.ngs1);
        board2.teleport(destination_asterism.ngs2);
        board3.teleport(destination_asterism.ngs3);
    }
    if (targets == Board_set_targets::ngs_132) {
        board1.teleport(destination_asterism.ngs1);
        board2.teleport(destination_asterism.ngs3);
        board3.teleport(destination_asterism.ngs2);
    }
    if (targets == Board_set_targets::ngs_213) {
        board1.teleport(destination_asterism.ngs2);
        board2.teleport(destination_asterism.ngs1);
        board3.teleport(destination_asterism.ngs3);
    }
    if (targets == Board_set_targets::ngs_231) {
        board1.teleport(destination_asterism.ngs2);
        board2.teleport(destination_asterism.ngs3);
        board3.teleport(destination_asterism.ngs1);
    }
    if (targets == Board_set_targets::ngs_312) {
        board1.teleport(destination_asterism.ngs3);
        board2.teleport(destination_asterism.ngs1);
        board3.teleport(destination_asterism.ngs2);
    }
    if (targets == Board_set_targets::ngs_321) {
        board1.teleport(destination_asterism.ngs3);
        board2.teleport(destination_asterism.ngs2);
        board3.teleport(destination_asterism.ngs1);
    }
    if (targets == Board_set_targets::none)
        std::cout << "Warning: attempted to teleport boards but 'targets' field is 'none'" << std::endl;
}

void Board_set::draw (const Asterism& asterism) const {
    Polygon ngs_triangle;
    ngs_triangle.push_back(asterism.ngs1);
    ngs_triangle.push_back(asterism.ngs2);
    ngs_triangle.push_back(asterism.ngs3);

    PolygonSet polys;
    polys.insert(ngs_triangle);
    polys.insert(board1.profile);
    polys.insert(board2.profile);
    polys.insert(board3.profile);
    polys.insert(board1.pom_range);
    polys.insert(board2.pom_range);
    polys.insert(board3.pom_range);
    //polys.insert(FoV_small);
    //polys.insert(FoV_large);

    CGAL::draw(polys);
}

bool Board_set::move_step_linear_trajectory (const Asterism& destination_asterism, const double distance_step) {
    if (targets == Board_set_targets::ngs_123) {
        board1.move_step_linear_trajectory(destination_asterism.ngs1, distance_step);
        board2.move_step_linear_trajectory(destination_asterism.ngs2, distance_step);
        board3.move_step_linear_trajectory(destination_asterism.ngs3, distance_step);
    }
    else if (targets == Board_set_targets::ngs_132) {
        board1.move_step_linear_trajectory(destination_asterism.ngs1, distance_step);
        board2.move_step_linear_trajectory(destination_asterism.ngs3, distance_step);
        board3.move_step_linear_trajectory(destination_asterism.ngs2, distance_step);
    }
    else if (targets == Board_set_targets::ngs_213) {
        board1.move_step_linear_trajectory(destination_asterism.ngs2, distance_step);
        board2.move_step_linear_trajectory(destination_asterism.ngs1, distance_step);
        board3.move_step_linear_trajectory(destination_asterism.ngs3, distance_step);
    }
    else if (targets == Board_set_targets::ngs_231) {
        board1.move_step_linear_trajectory(destination_asterism.ngs2, distance_step);
        board2.move_step_linear_trajectory(destination_asterism.ngs3, distance_step);
        board3.move_step_linear_trajectory(destination_asterism.ngs1, distance_step);
    }
    else if (targets == Board_set_targets::ngs_312) {
        board1.move_step_linear_trajectory(destination_asterism.ngs3, distance_step);
        board2.move_step_linear_trajectory(destination_asterism.ngs1, distance_step);
        board3.move_step_linear_trajectory(destination_asterism.ngs2, distance_step);
    }
    else if (targets == Board_set_targets::ngs_321) {
        board1.move_step_linear_trajectory(destination_asterism.ngs3, distance_step);
        board2.move_step_linear_trajectory(destination_asterism.ngs2, distance_step);
        board3.move_step_linear_trajectory(destination_asterism.ngs1, distance_step);
    }
    else if (targets == Board_set_targets::none) {
        std::cout << "Warning: attempted to move boards but 'targets' field is 'none'" << std::endl;
        return false;
    }

    return detect_collision();
}

bool Board_set::is_destination_reached (const Asterism& destination_asterism) const {
    if (targets == Board_set_targets::ngs_123)
        return (board1.is_destination_reached(destination_asterism.ngs1) && board2.is_destination_reached(destination_asterism.ngs2) && board3.is_destination_reached(destination_asterism.ngs3));

    if (targets == Board_set_targets::ngs_132)
        return (board1.is_destination_reached(destination_asterism.ngs1) && board2.is_destination_reached(destination_asterism.ngs3) && board3.is_destination_reached(destination_asterism.ngs2));

    if (targets == Board_set_targets::ngs_213)
        return (board1.is_destination_reached(destination_asterism.ngs2) && board2.is_destination_reached(destination_asterism.ngs1) && board3.is_destination_reached(destination_asterism.ngs3));

    if (targets == Board_set_targets::ngs_231)
        return (board1.is_destination_reached(destination_asterism.ngs2) && board2.is_destination_reached(destination_asterism.ngs3) && board3.is_destination_reached(destination_asterism.ngs1));

    if (targets == Board_set_targets::ngs_312)
        return (board1.is_destination_reached(destination_asterism.ngs3) && board2.is_destination_reached(destination_asterism.ngs1) && board3.is_destination_reached(destination_asterism.ngs2));

    if (targets == Board_set_targets::ngs_321)
        return (board1.is_destination_reached(destination_asterism.ngs3) && board2.is_destination_reached(destination_asterism.ngs2) && board3.is_destination_reached(destination_asterism.ngs1));

    if (targets == Board_set_targets::none) {
        std::cout << "Warning: attempted to move boards but 'targets' field is 'none'" << std::endl;
        return false;
    }

    return false;
}

void Board_set::draw () const {
    PolygonSet polys;
    polys.insert(board1.profile);
    polys.insert(board2.profile);
    polys.insert(board3.profile);
    polys.insert(board1.pom_range);
    polys.insert(board2.pom_range);
    polys.insert(board3.pom_range);
    //polys.insert(FoV_small);
    //polys.insert(FoV_large);

    CGAL::draw(polys);
}

double Board_set::calculate_distance (const Asterism& destination_asterism) const {
    double total_distance = 0.;

    if (targets == Board_set_targets::ngs_123) {
        total_distance += board1.calculate_distance(destination_asterism.ngs1);
        total_distance += board2.calculate_distance(destination_asterism.ngs2);
        total_distance += board3.calculate_distance(destination_asterism.ngs3);
    }
    else if (targets == Board_set_targets::ngs_132) {
        total_distance += board1.calculate_distance(destination_asterism.ngs1);
        total_distance += board2.calculate_distance(destination_asterism.ngs3);
        total_distance += board3.calculate_distance(destination_asterism.ngs2);
    }
    else if (targets == Board_set_targets::ngs_213) {
        total_distance += board1.calculate_distance(destination_asterism.ngs2);
        total_distance += board2.calculate_distance(destination_asterism.ngs1);
        total_distance += board3.calculate_distance(destination_asterism.ngs3);
    }
    else if (targets == Board_set_targets::ngs_231) {
        total_distance += board1.calculate_distance(destination_asterism.ngs2);
        total_distance += board2.calculate_distance(destination_asterism.ngs3);
        total_distance += board3.calculate_distance(destination_asterism.ngs1);
    }
    else if (targets == Board_set_targets::ngs_312) {
        total_distance += board1.calculate_distance(destination_asterism.ngs3);
        total_distance += board2.calculate_distance(destination_asterism.ngs1);
        total_distance += board3.calculate_distance(destination_asterism.ngs2);
    }
    else if (targets == Board_set_targets::ngs_321) {
        total_distance += board1.calculate_distance(destination_asterism.ngs3);
        total_distance += board2.calculate_distance(destination_asterism.ngs2);
        total_distance += board3.calculate_distance(destination_asterism.ngs1);
    }
    else if (targets == Board_set_targets::none) {
        total_distance = std::numeric_limits<double>::infinity();
        std::cout << "Warning: attempted to calculate distance but 'targets' field is 'none'" << std::endl;
    }

    return total_distance;
}

void Board_set::move_step_out_of_technical_field (double distance_step) {
        board1.move_step_out_of_technical_field(technical_field, distance_step);
        board2.move_step_out_of_technical_field(technical_field, distance_step);
        board3.move_step_out_of_technical_field(technical_field, distance_step);
}

bool Board_set::is_in_technical_field () const {
    if (board1.is_in_technical_field(technical_field) && board2.is_in_technical_field(technical_field) && board3.is_in_technical_field(technical_field))
        return true;

    return false;
}
