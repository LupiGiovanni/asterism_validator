#include "Asterism.h"
#include "Board.h"
#include "Board_set.h"
#include "Simulation.h"
#include "helper.h"
#include "dataset.h"
#include "Simulation_manager.h"
#include "Graphic_viewer.h"

int main () {
    //Simulation_manager::simulate_dataset(Movement::linear_trajectory, cedric_dataset);
    //Simulation_manager::simulate_dataset(Movement::linear_trajectory, cedric_dataset_extended);
    //Simulation_manager::simulate_dataset(Movement::safe_basic, cedric_dataset_extended);

    Graphic_viewer gv;
    gv.animate(Movement::safe_basic, cedric_dataset[9], cedric_dataset[11]);

    //Simulation_manager::simulate_random_dataset(Movement::linear_trajectory);
    //Simulation_manager::simulate_random_dataset(Movement::safe_basic);

    return 0;
}