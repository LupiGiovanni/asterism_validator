#include "Asterism.h"
#include "Board.h"
#include "Board_set.h"
#include "Simulation.h"
#include "helper.h"
#include "dataset.h"
#include "Simulation_manager.h"
#include "Graphic_viewer.h"

int main () {
    Board_set bs;
    Graphic_viewer gv;
    gv.animate(Movement::linear_trajectory, cedric_dataset[0], cedric_dataset[4]);
    return 0;
}