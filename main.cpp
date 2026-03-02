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
    // Simulation_manager::simulate_dataset(Movement::safe_basic, cedric_dataset_extended);

    // Graphic_viewer gv;
    // gv.animate(Movement::linear_trajectory, cedric_dataset[0], cedric_dataset[4]);

    //Simulation_manager::simulate_random_dataset(Movement::linear_trajectory);
    //Simulation_manager::simulate_random_dataset(Movement::safe_basic);

    Asterism start (-129.79312,-166.46211,75.734436,205.7975,-189.29662,-177.28346);
    Asterism destination (45.393715,27.85892,0.0,169.01007,-190.43402,0.0);

    Simulation_manager::simulate(Movement::linear_trajectory, start, destination);
    Graphic_viewer gv;
    gv.animate(Movement::linear_trajectory, start, destination);

    return 0;
}