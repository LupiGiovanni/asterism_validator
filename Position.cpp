//
// Created by gionimbus on 3/10/26.
//

#include "Position.h"

Position::Position (int x, int y): x(x), y(y) {}

bool Position::operator == (const Position& other) const {
    return x == other.x && y == other.y;
}

int Position::get_x() const {
    return x;
}

int Position::get_y() const {
    return y;
}

void Position::print() const {
    std::cout << "(" << x << ", " << y << ")";
}