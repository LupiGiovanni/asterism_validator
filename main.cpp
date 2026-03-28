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
    Simulation s;
    Board_set boards;
    Graphic_viewer gv;

    //gv.animate(Movement::A_star, cedric_dataset[11], cedric_dataset[300]);
    gv.animate(Movement::A_star, cedric_dataset[2], cedric_dataset[3]);
    //
    // for (int i = 0; i < cedric_dataset.size() - 2; ++i)
    //     gv.animate(Movement::A_star, cedric_dataset[i], cedric_dataset[i+1]);

    //Simulation_manager::simulate_dataset(Movement::linear, cedric_dataset);

    return 0;
}