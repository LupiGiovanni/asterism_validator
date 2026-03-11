//
// Created by gionimbus on 3/10/26.
//

#include "Board_state.h"

Board_state::Board_state (long x, long y): x(x), y(y) {}

bool Board_state::operator == (const Board_state& other) const {
    return x == other.x && y == other.y;
}

long Board_state::get_x() const {
    return x;
}

long Board_state::get_y() const {
    return y;
}

void Board_state::print() const {
    std::cout << "(" << x << ", " << y << ")";
}