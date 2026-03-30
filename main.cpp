
#include "Simulation.h"
#include "Simulation_manager.h"
#include "Graphic_viewer.h"
#include "Dataset_generator.h"
#include "dataset.h"

int main () {
    Simulation s;
    Graphic_viewer gv;
    Dataset_generator dg;

    // gv.animate(Movement::A_star, cedric_dataset[11], cedric_dataset[300]);
    // gv.animate(Movement::A_star, cedric_dataset[2], cedric_dataset[3]);
    //
    // for (int i = 0; i < cedric_dataset.size() - 2; ++i)
    //     gv.animate(Movement::A_star, cedric_dataset[i], cedric_dataset[i+1]);

    //Simulation_manager::simulate_dataset(Movement::safe_basic, cedric_dataset);

    dg.generate_dataset_random_valid();
    for (int i = 0; i < dg.get_dataset().size() - 2; ++i)
        gv.animate(Movement::A_star, dg.get_dataset()[i], dg.get_dataset()[i+1]);

    return 0;
}