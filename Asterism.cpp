//
// Created by gionimbus on 12/16/25.
//

#include "global_functions.h"
#include "Asterism.h"

Asterism::Asterism(double ngs1_x, double ngs2_x, double ngs3_x, double ngs1_y, double ngs2_y, double ngs3_y) {
    ngs1 = Point(ngs1_x, ngs1_y);
    ngs2 = Point(ngs2_x, ngs2_y);
    ngs3 = Point(ngs3_x, ngs3_y);
}

bool Asterism::is_valid (Board &board_1, Board &board_2, Board &board_3) const {

    reset_boards(board_1, board_2, board_3);

    if (board_1.move_to_ngs(ngs1)
        && board_2.move_to_ngs(ngs2)
        && board_3.move_to_ngs(ngs3)
        && !detect_collision(board_1, board_2, board_3))
        return true;

    reset_boards(board_1, board_2, board_3);

    if (board_1.move_to_ngs(ngs1)
        && board_2.move_to_ngs(ngs3)
        && board_3.move_to_ngs(ngs2)
        && !detect_collision(board_1, board_2, board_3))
        return true;

    reset_boards(board_1, board_2, board_3);

    if (board_1.move_to_ngs(ngs2)
        && board_2.move_to_ngs(ngs1)
        && board_3.move_to_ngs(ngs3)
        && !detect_collision(board_1, board_2, board_3))
        return true;

    reset_boards(board_1, board_2, board_3);

    if (board_1.move_to_ngs(ngs2)
        && board_2.move_to_ngs(ngs3)
        && board_3.move_to_ngs(ngs1)
        && !detect_collision(board_1, board_2, board_3))
        return true;

    reset_boards(board_1, board_2, board_3);

    if (board_1.move_to_ngs(ngs3)
        && board_2.move_to_ngs(ngs1)
        && board_3.move_to_ngs(ngs2)
        && !detect_collision(board_1, board_2, board_3))
        return true;

    reset_boards(board_1, board_2, board_3);

    if (board_1.move_to_ngs(ngs3)
        && board_2.move_to_ngs(ngs2)
        && board_3.move_to_ngs(ngs1)
        && !detect_collision(board_1, board_2, board_3))
        return true;

    return false;
}

