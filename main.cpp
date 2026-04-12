
#include "Simulation.h"
#include "Simulation_manager.h"
#include "Graphic_viewer.h"
#include "Dataset_generator.h"
#include "datasets.h"

int main () {
    Graphic_viewer gv;
    Dataset_generator dg;


    // dg.generate_dataset();
    // std::vector<Asterism> hard_mode_dataset = dg.get_dataset();
    //
    // for (int i = 1; i < hard_mode_dataset.size(); ++i)
    //     gv.animate(Movement::A_star, hard_mode_dataset[i-1], hard_mode_dataset[i]);


    for (int i = 1; i < cedric_dataset.size(); ++i)
        gv.animate(Movement::A_star, cedric_dataset[i-1], cedric_dataset[i]);


    return 0;
}