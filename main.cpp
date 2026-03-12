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
    // State start (-27,-125,58,252,124,-193);
    // State goal (161,-52,179,139,220,-182);
    //
    // std::vector<State> path = A_star::search (start, goal);
    //
    // std::cout << "Path from start to goal:" << std::endl;
    // for (const auto& state : path)
    //     state.print();

    Simulation_manager::simulate(Movement::A_star, cedric_dataset[0], cedric_dataset[1]);

    return 0;
}