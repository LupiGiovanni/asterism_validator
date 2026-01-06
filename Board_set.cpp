//
// Created by gionimbus on 12/30/25.
//

#include "Board_set.h"

Board_set::Board_set(): board1(Board_type::type_1), board2(Board_type::type_2), board3(Board_type::type_3), assignment(Board_assignment::none) {
    Point R(-87.847500, -87.847500);
    Point S(87.847500, -87.847500);
    Point T(87.847500, 87.847500);
    Point U(-87.847500, 87.847500);

    fov_small.push_back(R);
    fov_small.push_back(S);
    fov_small.push_back(T);
    fov_small.push_back(U);

    Point V(-33.150000, -33.150000);
    Point W(33.150000, -33.150000);
    Point X(33.150000, 33.150000);
    Point Y(-33.150000, 33.150000);

    fov_large.push_back(V);
    fov_large.push_back(W);
    fov_large.push_back(X);
    fov_large.push_back(Y);
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

void Board_set::assign_ngs (const Asterism& asterism) {
    Point pom1_prev = board1.pom;
    Point pom2_prev = board2.pom;
    Point pom3_prev = board3.pom;

    if (board1.teleport(asterism.ngs1) && board2.teleport(asterism.ngs2) && board3.teleport(asterism.ngs3) && !detect_collision()) {
        assignment = Board_assignment::ngs_123;
        board1.teleport(pom1_prev);
        board2.teleport(pom2_prev);
        board3.teleport(pom3_prev);
    }

    if (board1.teleport(asterism.ngs1) && board2.teleport(asterism.ngs3) && board3.teleport(asterism.ngs2) && !detect_collision()) {
        assignment = Board_assignment::ngs_132;
        board1.teleport(pom1_prev);
        board2.teleport(pom2_prev);
        board3.teleport(pom3_prev);
    }

    if (board1.teleport(asterism.ngs2) && board2.teleport(asterism.ngs1) && board3.teleport(asterism.ngs3) && !detect_collision()) {
        assignment = Board_assignment::ngs_213;
        board1.teleport(pom1_prev);
        board2.teleport(pom2_prev);
        board3.teleport(pom3_prev);
    }

    if (board1.teleport(asterism.ngs2) && board2.teleport(asterism.ngs3) && board3.teleport(asterism.ngs1) && !detect_collision()) {
        assignment = Board_assignment::ngs_231;
        board1.teleport(pom1_prev);
        board2.teleport(pom2_prev);
        board3.teleport(pom3_prev);
    }

    if (board1.teleport(asterism.ngs3) && board2.teleport(asterism.ngs1) && board3.teleport(asterism.ngs2) && !detect_collision()) {
        assignment = Board_assignment::ngs_312;
        board1.teleport(pom1_prev);
        board2.teleport(pom2_prev);
        board3.teleport(pom3_prev);
    }

    if (board1.teleport(asterism.ngs3) && board2.teleport(asterism.ngs2) && board3.teleport(asterism.ngs1) && !detect_collision()) {
        assignment = Board_assignment::ngs_321;
        board1.teleport(pom1_prev);
        board2.teleport(pom2_prev);
        board3.teleport(pom3_prev);
    }

    assignment = Board_assignment::none;
    board1.teleport(pom1_prev);
    board2.teleport(pom2_prev);
    board3.teleport(pom3_prev);
}

bool Board_set::teleport (const Asterism& asterism) {
    if (assignment == Board_assignment::ngs_123) {
        board1.teleport(asterism.ngs1);
        board2.teleport(asterism.ngs2);
        board3.teleport(asterism.ngs3);
        return true;
    }
    if (assignment == Board_assignment::ngs_132) {
        board1.teleport(asterism.ngs1);
        board2.teleport(asterism.ngs3);
        board3.teleport(asterism.ngs2);
        return true;
    }
    if (assignment == Board_assignment::ngs_213) {
        board1.teleport(asterism.ngs2);
        board2.teleport(asterism.ngs1);
        board3.teleport(asterism.ngs3);
        return true;
    }
    if (assignment == Board_assignment::ngs_231) {
        board1.teleport(asterism.ngs2);
        board2.teleport(asterism.ngs3);
        board3.teleport(asterism.ngs1);
        return true;
    }
    if (assignment == Board_assignment::ngs_312) {
        board1.teleport(asterism.ngs3);
        board2.teleport(asterism.ngs1);
        board3.teleport(asterism.ngs2);
        return true;
    }
    if (assignment == Board_assignment::ngs_321) {
        board1.teleport(asterism.ngs3);
        board2.teleport(asterism.ngs2);
        board3.teleport(asterism.ngs1);
        return true;
    }
    return false;
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

bool Board_set::move_step_linear (const Asterism& asterism, const double step_mm) {
    if (assignment == Board_assignment::ngs_123) {
        board1.move_step_linear(asterism.ngs1, step_mm);
        board2.move_step_linear(asterism.ngs2, step_mm);
        board3.move_step_linear(asterism.ngs3, step_mm);
    }
    else if (assignment == Board_assignment::ngs_132) {
        board1.move_step_linear(asterism.ngs1, step_mm);
        board2.move_step_linear(asterism.ngs3, step_mm);
        board3.move_step_linear(asterism.ngs2, step_mm);
    }
    else if (assignment == Board_assignment::ngs_213) {
        board1.move_step_linear(asterism.ngs2, step_mm);
        board2.move_step_linear(asterism.ngs1, step_mm);
        board3.move_step_linear(asterism.ngs3, step_mm);
    }
    else if (assignment == Board_assignment::ngs_231) {
        board1.move_step_linear(asterism.ngs2, step_mm);
        board2.move_step_linear(asterism.ngs3, step_mm);
        board3.move_step_linear(asterism.ngs1, step_mm);
    }
    else if (assignment == Board_assignment::ngs_312) {
        board1.move_step_linear(asterism.ngs3, step_mm);
        board2.move_step_linear(asterism.ngs1, step_mm);
        board3.move_step_linear(asterism.ngs2, step_mm);
    }
    else if (assignment == Board_assignment::ngs_321) {
        board1.move_step_linear(asterism.ngs3, step_mm);
        board2.move_step_linear(asterism.ngs2, step_mm);
        board3.move_step_linear(asterism.ngs1, step_mm);
    }

    bool collision_detected = detect_collision();

    return collision_detected;
}

