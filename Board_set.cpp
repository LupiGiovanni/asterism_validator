//
// Created by gionimbus on 12/30/25.
//

#include "Board_set.h"

// For a graphical reference of the coordinates below see attached documentation
Board_set::Board_set(): board1(Board_type::type1), board2(Board_type::type2),board3(Board_type::type3),
                        current_asterism(Asterism(0.,0.,0.,0.,0.,0.)),
                        valid_permutations({}) {

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

void Board_set::set_current_asterism (const Asterism& asterism) {
    current_asterism = asterism;
}

std::vector<Asterism> Board_set::calculate_all_permutations (const Asterism& asterism) {
    std::vector<Asterism> permutations;

    permutations.push_back(Asterism(asterism.ngs1.x(), asterism.ngs2.x(), asterism.ngs3.x(), asterism.ngs1.y(), asterism.ngs2.y(), asterism.ngs3.y()));
    permutations.push_back(Asterism(asterism.ngs1.x(), asterism.ngs3.x(), asterism.ngs2.x(), asterism.ngs1.y(), asterism.ngs3.y(), asterism.ngs2.y()));
    permutations.push_back(Asterism(asterism.ngs2.x(), asterism.ngs1.x(), asterism.ngs3.x(), asterism.ngs2.y(), asterism.ngs1.y(), asterism.ngs3.y()));
    permutations.push_back(Asterism(asterism.ngs2.x(), asterism.ngs3.x(), asterism.ngs1.x(), asterism.ngs2.y(), asterism.ngs3.y(), asterism.ngs1.y()));
    permutations.push_back(Asterism(asterism.ngs3.x(), asterism.ngs1.x(), asterism.ngs2.x(), asterism.ngs3.y(), asterism.ngs1.y(), asterism.ngs2.y()));
    permutations.push_back(Asterism(asterism.ngs3.x(), asterism.ngs2.x(), asterism.ngs1.x(), asterism.ngs3.y(), asterism.ngs2.y(), asterism.ngs1.y()));

    return permutations;
}

void Board_set::calculate_valid_permutations () {
    if (const Asterism zero_asterism; current_asterism == zero_asterism) {
        std::cout << "Warning: current asterism is not set. Call Board_set::set_current_asterism before calculating assignments." << std::endl;
        return;
    }

    valid_permutations.clear();
    std::vector<Asterism> permutations = calculate_all_permutations(current_asterism);
    Board_set temporary = *this;

    for (int i = 0; i < permutations.size(); ++i)
        if (temporary.board1.teleport(permutations[i].ngs1) && temporary.board2.teleport(permutations[i].ngs2) && temporary.board3.teleport(permutations[i].ngs3) && !temporary.detect_collision())
            valid_permutations.push_back(permutations[i]);
}

bool Board_set::is_valid_permutation (const Asterism& asterism) const {
    for (const auto& it: valid_permutations)
        if (asterism == it)
            return true;

    return false;
}

bool Board_set::teleport (const Asterism& destination_asterism) {

    if (is_valid_permutation(destination_asterism)) {
        board1.teleport(destination_asterism.ngs1);
        board2.teleport(destination_asterism.ngs2);
        board3.teleport(destination_asterism.ngs3);
        return true;
    }

    std::cout << "Warning: attempted teleportation to an invalid permutation." << std::endl;
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

bool Board_set::move_step_linear (const Asterism& destination_asterism, const double distance_step) {
    if (!is_valid_permutation(destination_asterism)) {
        std::cout << "Warning: attempted to move towards an invalid permutation." << std::endl;
        return false;
    }

    board1.move_step_linear(destination_asterism.ngs1, distance_step);
    board2.move_step_linear(destination_asterism.ngs2, distance_step);
    board3.move_step_linear(destination_asterism.ngs3, distance_step);

   return detect_collision();
}

bool Board_set::is_destination_reached (const Asterism& destination_asterism) const {
    if (!is_valid_permutation(destination_asterism)) {
        std::cout << "Warning: attempted to check destination reached for an invalid permutation." << std::endl;
        return false;
    }

    if (board1.is_destination_reached(destination_asterism.ngs1) && board2.is_destination_reached(destination_asterism.ngs2) && board3.is_destination_reached(destination_asterism.ngs3))
        return true;

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