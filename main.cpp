#include <iostream>
#include "dataset.h"
#include "global_functions.h"
#include "Board.h"
#include "Board_set.h"
#include "Asterism.h"
#include "Simulation.h"

int main() {
    Board_set boards;
    Simulation simulation;
    simulation.linear_trajectory(boards, dataset[0], dataset[1]);
    simulation.print_results();

    return 0;
}