#include <iostream>
#include "dataset.h"
#include "Asterism.h"
#include "Board.h"
#include "Board_set.h"
#include "Simulation.h"
#include "Dataset_generator.h"
#include "helper.h"

int main() {
    Dataset_generator generator;
    generator.generate_random_valid_dataset();

    // dataset_run_simulation_linear_trajectory(generator.dataset);
    dataset_run_simulation_out_of_technical_field(generator.dataset);

    return 0;
}