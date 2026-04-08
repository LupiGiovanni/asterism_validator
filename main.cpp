
#include "Simulation.h"
#include "Simulation_manager.h"
#include "Graphic_viewer.h"
#include "Dataset_generator.h"
#include "dataset.h"

int main () {
    Simulation_manager::simulate_dataset(Movement::linear, cedric_dataset);

    return 0;
}