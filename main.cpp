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
    const std::vector<Asterism>& dataset = generator.get_dataset();

    // dataset_run_simulation_linear_trajectory(dataset);
    dataset_run_simulation_out_of_technical_field(dataset);

    return 0;
}