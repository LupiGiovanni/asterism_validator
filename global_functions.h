//
// Created by gionimbus on 12/16/25.
//

#ifndef ASTERISM_VALIDATOR_GLOBAL_FUNCTIONS_H
#define ASTERISM_VALIDATOR_GLOBAL_FUNCTIONS_H

#include"Board.h"
#include"Asterism.h"

bool detect_collision (const Board& board_1, const Board& board_2, const Board& board_3) {
    bool detected = true;

    if (!CGAL::do_intersect(board_1.profile, board_2.profile)
        && !CGAL::do_intersect(board_1.profile, board_3.profile)
        && !CGAL::do_intersect(board_2.profile, board_3.profile)) {
        detected = false;
    }

    return detected;
}

void draw (const Asterism& asterism, const Board& board_1, const Board& board_2, const Board& board_3) {
    Polygon ngs_triangle;
    ngs_triangle.push_back(asterism.ngs1);
    ngs_triangle.push_back(asterism.ngs2);
    ngs_triangle.push_back(asterism.ngs3);

    PolygonSet polys;
    polys.insert(ngs_triangle);
    polys.insert(board_1.profile);
    polys.insert(board_2.profile);
    polys.insert(board_3.profile);
    polys.insert(board_1.pom_range);
    polys.insert(board_2.pom_range);
    polys.insert(board_3.pom_range);

    CGAL::draw(polys);
}

#endif //ASTERISM_VALIDATOR_GLOBAL_FUNCTIONS_H