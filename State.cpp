//
// Created by gionimbus on 3/10/26.
//

#include "State.h"

State::State (): s{} {}

State::State(const Board_state& s0, const Board_state& s1, const Board_state& s2) : s{s0, s1, s2} {}

State::State(long s0_x, long s1_x, long s2_x, long s0_y, long s1_y, long s2_y) : s{Board_state(s0_x, s0_y), Board_state(s1_x, s1_y), Board_state(s2_x, s2_y)} {}

std::vector<Board_state> State::get_s() const {
    return s;
}

bool State::operator == (const State& other) const {
    return s[0] == other.s[0] && s[1] == other.s[1] && s[2] == other.s[2];
}

void State::print() const {
    for (const auto& bs : s) {
        bs.print();
        std::cout << " ";
    }
    std::cout << std::endl;
}