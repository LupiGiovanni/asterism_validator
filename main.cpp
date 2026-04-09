
#include "Simulation.h"
#include "Simulation_manager.h"
#include "Graphic_viewer.h"
#include "Dataset_generator.h"
#include "datasets.h"

int main () {
    Graphic_viewer gv;

    for (int i = 1; i < cedric_dataset.size() - 1; ++i) {
        gv.animate(Movement::A_star, cedric_dataset[i-1], cedric_dataset[i]);
    }

    return 0;
}