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

    Asterism start_a (-76.305647, 158.618230, -136.754214, -36.137091, -111.701498, 217.041397);
    Asterism goal_a (122.718571, -33.932973, 249.711987, 36.378866, 260.887333, -54.757124);

    Asterism start_b (232.223713, 66.640670, -41.871824, 116.354008, -112.966366, -165.532668);
    Asterism goal_b (-64.074902, -38.632346, 216.687889, 107.928191, -10.634813, 132.970463);

    Graphic_viewer gv;
    gv.animate(Movement::A_star, start_b, goal_b);

    return 0;
}