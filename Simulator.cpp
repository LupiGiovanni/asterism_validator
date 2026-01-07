//
// Created by gionimbus on 1/7/26.
//

#include "Simulator.h"

Simulator::Simulator (Board_set* boards, Asterism* asterism): boards(boards), asterism(asterism) {}

Simulator::Simulator (): boards(nullptr), asterism(nullptr) {}

void Simulator::set_boards (Board_set* new_boards) {
    boards = new_boards;
}

void Simulator::set_asterism(Asterism* new_asterism) {
    asterism = new_asterism;
}

