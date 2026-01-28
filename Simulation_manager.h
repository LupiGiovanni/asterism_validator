//
// Created by gionimbus on 1/26/26.
//

#ifndef ASTERISM_VALIDATOR_SIMULATION_MANAGER_H
#define ASTERISM_VALIDATOR_SIMULATION_MANAGER_H

#include "Asterism.h"
#include "Simulation.h"
#include "Dataset_generator.h"
#include "Graphic_viewer.h" // for debugging visualization
                            // TODO: remove later

class Simulation_manager {
public:
    static void simulate_dataset (Movement movement_type, const std::vector<Asterism>& dataset);

    static void simulate_random_dataset (Movement movement_type);

private:
    static void simulate_dataset_linear_trajectory (const std::vector<Asterism>& dataset);
    static void simulate_dataset_outside_tech_field (const std::vector<Asterism>& dataset);
};


#endif //ASTERISM_VALIDATOR_SIMULATION_MANAGER_H