//
// Created by gionimbus on 3/10/26.
//

#include "State.h"

State::State (): pos{} {}

State::State(const Position& pos0, const Position& pos1, const Position& pos2) : pos{pos0, pos1, pos2} {}

State::State(int pos0_x, int pos1_x, int pos2_x, int pos0_y, int pos1_y, int pos2_y) :
    pos{Position(pos0_x, pos0_y), Position(pos1_x, pos1_y), Position(pos2_x, pos2_y)} {}

State::State(const Asterism& asterism):
    State(static_cast<int>(std::round(asterism.get_ngs(0).x())),
          static_cast<int>(std::round(asterism.get_ngs(1).x())),
          static_cast<int>(std::round(asterism.get_ngs(2).x())),
          static_cast<int>(std::round(asterism.get_ngs(0).y())),
          static_cast<int>(std::round(asterism.get_ngs(1).y())),
          static_cast<int>(std::round(asterism.get_ngs(2).y())) ) {}

std::vector<Position> State::get_positions() const {
    return pos;
}

bool State::operator == (const State& other) const {
    return pos[0] == other.pos[0] && pos[1] == other.pos[1] && pos[2] == other.pos[2];
}

void State::print() const {
    for (const auto& bs : pos) {
        bs.print();
        std::cout << " ";
    }
    std::cout << std::endl;
}