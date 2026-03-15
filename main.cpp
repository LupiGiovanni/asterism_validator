#include "Asterism.h"
#include "Board.h"
#include "Board_set.h"
#include "Simulation.h"
#include "helper.h"
#include "dataset.h"
#include "Simulation_manager.h"
#include "Graphic_viewer.h"
#include "A_star.h"

int main () {

    // State start (232.223713, 66.640670, -41.871824, 116.354008, -112.966366, -165.532668);
    // State goal (-64.074902, -38.632346, 216.687889, 107.928191, -10.634813, 132.970463);
    //
    // std::vector<State> path = A_star::search (start, goal);
    //
    // std::cout << "Path from start to goal:" << std::endl;
    // for (const auto& state : path)
    //     state.print();

    Asterism start_a (232.223713, 66.640670, -41.871824, 116.354008, -112.966366, -165.532668);
    Asterism goal_a (-64.074902, -38.632346, 216.687889, 107.928191, -10.634813, 132.970463);

    Graphic_viewer gv;
    gv.animate(Movement::A_star, start_a, goal_a);

    //Simulation_manager::simulate(Movement::A_star, start_a, goal_a);

    return 0;
}