//
// Created by gionimbus on 12/30/25.
//

#include "Board_set.h"

// For a graphical reference of the coordinates below see attached documentation
Board_set::Board_set(): board1(Board_type::type1), board2(Board_type::type2),board3(Board_type::type3), targets(Board_set_targets::none), secondary_targets(Board_set_targets::none) {

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
    bool assigned = false;
    Board_set_targets targets1 = Board_set_targets::none;
    Board_set_targets targets2 = Board_set_targets::none;

    if (temporary.board1.teleport(destination_asterism.ngs1) && temporary.board2.teleport(destination_asterism.ngs2) && temporary.board3.teleport(destination_asterism.ngs3) && !temporary.detect_collision()) {
        targets1 = Board_set_targets::ngs_123;
        assigned = true;
    }

    if (temporary.board1.teleport(destination_asterism.ngs1) && temporary.board2.teleport(destination_asterism.ngs3) && temporary.board3.teleport(destination_asterism.ngs2) && !temporary.detect_collision()) {
        if (assigned == false) {
            targets1 = Board_set_targets::ngs_132;
            assigned = true;
        }
        else
            targets2 = Board_set_targets::ngs_132;
    }

    if (temporary.board1.teleport(destination_asterism.ngs2) && temporary.board2.teleport(destination_asterism.ngs1) && temporary.board3.teleport(destination_asterism.ngs3) && !temporary.detect_collision()) {
        if (assigned == false) {
            targets1 = Board_set_targets::ngs_213;
            assigned = true;
        }
        else
            targets2 = Board_set_targets::ngs_213;
    }

    if (temporary.board1.teleport(destination_asterism.ngs2) && temporary.board2.teleport(destination_asterism.ngs3) && temporary.board3.teleport(destination_asterism.ngs1) && !temporary.detect_collision()) {
        if (assigned == false) {
            targets1 = Board_set_targets::ngs_231;
            assigned = true;
        }
        else
            targets2 = Board_set_targets::ngs_231;
    }

    if (temporary.board1.teleport(destination_asterism.ngs3) && temporary.board2.teleport(destination_asterism.ngs1) && temporary.board3.teleport(destination_asterism.ngs2) && !temporary.detect_collision()) {
        if (assigned == false) {
            targets1 = Board_set_targets::ngs_312;
            assigned = true;
        }
        else
            targets2 = Board_set_targets::ngs_312;
    }

    if (temporary.board1.teleport(destination_asterism.ngs3) && temporary.board2.teleport(destination_asterism.ngs2) && temporary.board3.teleport(destination_asterism.ngs1) && !temporary.detect_collision()) {
        if (assigned == false) {
            targets1 = Board_set_targets::ngs_321;
            assigned = true;
        }
        else
            targets2 = Board_set_targets::ngs_321;
    }

    // This part ensures that if two valid assignments are found, the one with the minor distance is stored in 'targets'
    double distance1 = calculate_distance(destination_asterism, targets1);
    double distance2 = calculate_distance(destination_asterism, targets2);

    if (distance1 > distance2) {
        Board_set_targets temp = targets1;
        targets1 = targets2;
        targets2 = temp;
    }

    targets = targets1;
    secondary_targets = targets2;
}

void Board_set::teleport (const Asterism& destination_asterism, const Board_set_targets specific_targets) {
    // assign_targets(destination_asterism);

    if (specific_targets == Board_set_targets::ngs_123) {
        board1.teleport(destination_asterism.ngs1);
        board2.teleport(destination_asterism.ngs2);
        board3.teleport(destination_asterism.ngs3);
    }
    else if (specific_targets == Board_set_targets::ngs_132) {
        board1.teleport(destination_asterism.ngs1);
        board2.teleport(destination_asterism.ngs3);
        board3.teleport(destination_asterism.ngs2);
    }
    else if (specific_targets == Board_set_targets::ngs_213) {
        board1.teleport(destination_asterism.ngs2);
        board2.teleport(destination_asterism.ngs1);
        board3.teleport(destination_asterism.ngs3);
    }
    else if (specific_targets == Board_set_targets::ngs_231) {
        board1.teleport(destination_asterism.ngs2);
        board2.teleport(destination_asterism.ngs3);
        board3.teleport(destination_asterism.ngs1);
    }
    else if (specific_targets == Board_set_targets::ngs_312) {
        board1.teleport(destination_asterism.ngs3);
        board2.teleport(destination_asterism.ngs1);
        board3.teleport(destination_asterism.ngs2);
    }
    else if (specific_targets == Board_set_targets::ngs_321) {
        board1.teleport(destination_asterism.ngs3);
        board2.teleport(destination_asterism.ngs2);
        board3.teleport(destination_asterism.ngs1);
    }
    else if (specific_targets == Board_set_targets::none)
        std::cout << "Warning: no valid specific targets given." << std::endl;
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

bool Board_set::move_step_linear (const Asterism& destination_asterism, const Board_set_targets specific_targets, const double distance_step) {
    if (specific_targets == Board_set_targets::ngs_123) {
        board1.move_step_linear(destination_asterism.ngs1, distance_step);
        board2.move_step_linear(destination_asterism.ngs2, distance_step);
        board3.move_step_linear(destination_asterism.ngs3, distance_step);
    }
    else if (specific_targets == Board_set_targets::ngs_132) {
        board1.move_step_linear(destination_asterism.ngs1, distance_step);
        board2.move_step_linear(destination_asterism.ngs3, distance_step);
        board3.move_step_linear(destination_asterism.ngs2, distance_step);
    }
    else if (specific_targets == Board_set_targets::ngs_213) {
        board1.move_step_linear(destination_asterism.ngs2, distance_step);
        board2.move_step_linear(destination_asterism.ngs1, distance_step);
        board3.move_step_linear(destination_asterism.ngs3, distance_step);
    }
    else if (specific_targets == Board_set_targets::ngs_231) {
        board1.move_step_linear(destination_asterism.ngs2, distance_step);
        board2.move_step_linear(destination_asterism.ngs3, distance_step);
        board3.move_step_linear(destination_asterism.ngs1, distance_step);
    }
    else if (specific_targets == Board_set_targets::ngs_312) {
        board1.move_step_linear(destination_asterism.ngs3, distance_step);
        board2.move_step_linear(destination_asterism.ngs1, distance_step);
        board3.move_step_linear(destination_asterism.ngs2, distance_step);
    }
    else if (specific_targets == Board_set_targets::ngs_321) {
        board1.move_step_linear(destination_asterism.ngs3, distance_step);
        board2.move_step_linear(destination_asterism.ngs2, distance_step);
        board3.move_step_linear(destination_asterism.ngs1, distance_step);
    }
    else if (specific_targets == Board_set_targets::none) {
        std::cout << "Warning: attempted to move boards but 'targets' field is 'none'." << std::endl;
        return false;
    }

    return detect_collision();
}

bool Board_set::is_destination_reached (const Asterism& destination_asterism, const Board_set_targets specific_targets) const {
    if (specific_targets == Board_set_targets::ngs_123)
        return (board1.is_destination_reached(destination_asterism.ngs1) && board2.is_destination_reached(destination_asterism.ngs2) && board3.is_destination_reached(destination_asterism.ngs3));

    if (specific_targets == Board_set_targets::ngs_132)
        return (board1.is_destination_reached(destination_asterism.ngs1) && board2.is_destination_reached(destination_asterism.ngs3) && board3.is_destination_reached(destination_asterism.ngs2));

    if (specific_targets == Board_set_targets::ngs_213)
        return (board1.is_destination_reached(destination_asterism.ngs2) && board2.is_destination_reached(destination_asterism.ngs1) && board3.is_destination_reached(destination_asterism.ngs3));

    if (specific_targets == Board_set_targets::ngs_231)
        return (board1.is_destination_reached(destination_asterism.ngs2) && board2.is_destination_reached(destination_asterism.ngs3) && board3.is_destination_reached(destination_asterism.ngs1));

    if (specific_targets == Board_set_targets::ngs_312)
        return (board1.is_destination_reached(destination_asterism.ngs3) && board2.is_destination_reached(destination_asterism.ngs1) && board3.is_destination_reached(destination_asterism.ngs2));

    if (specific_targets == Board_set_targets::ngs_321)
        return (board1.is_destination_reached(destination_asterism.ngs3) && board2.is_destination_reached(destination_asterism.ngs2) && board3.is_destination_reached(destination_asterism.ngs1));

    if (specific_targets == Board_set_targets::none) {
        std::cout << "Warning: attempted to move boards but 'targets' field is 'none'." << std::endl;
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

double Board_set::calculate_distance (const Asterism& destination_asterism, const Board_set_targets specific_targets) const {
    double total_distance = 0.;

    if (specific_targets == Board_set_targets::ngs_123) {
        total_distance += board1.calculate_distance(destination_asterism.ngs1);
        total_distance += board2.calculate_distance(destination_asterism.ngs2);
        total_distance += board3.calculate_distance(destination_asterism.ngs3);
    }
    else if (specific_targets == Board_set_targets::ngs_132) {
        total_distance += board1.calculate_distance(destination_asterism.ngs1);
        total_distance += board2.calculate_distance(destination_asterism.ngs3);
        total_distance += board3.calculate_distance(destination_asterism.ngs2);
    }
    else if (specific_targets == Board_set_targets::ngs_213) {
        total_distance += board1.calculate_distance(destination_asterism.ngs2);
        total_distance += board2.calculate_distance(destination_asterism.ngs1);
        total_distance += board3.calculate_distance(destination_asterism.ngs3);
    }
    else if (specific_targets == Board_set_targets::ngs_231) {
        total_distance += board1.calculate_distance(destination_asterism.ngs2);
        total_distance += board2.calculate_distance(destination_asterism.ngs3);
        total_distance += board3.calculate_distance(destination_asterism.ngs1);
    }
    else if (specific_targets == Board_set_targets::ngs_312) {
        total_distance += board1.calculate_distance(destination_asterism.ngs3);
        total_distance += board2.calculate_distance(destination_asterism.ngs1);
        total_distance += board3.calculate_distance(destination_asterism.ngs2);
    }
    else if (specific_targets == Board_set_targets::ngs_321) {
        total_distance += board1.calculate_distance(destination_asterism.ngs3);
        total_distance += board2.calculate_distance(destination_asterism.ngs2);
        total_distance += board3.calculate_distance(destination_asterism.ngs1);
    }
    else if (specific_targets == Board_set_targets::none)
        total_distance = std::numeric_limits<double>::infinity();

    return total_distance;
}