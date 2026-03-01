//
// Created by gionimbus on 1/26/26.
//

#ifndef ASTERISM_VALIDATOR_SIMULATION_MANAGER_H
#define ASTERISM_VALIDATOR_SIMULATION_MANAGER_H

#include "Asterism.h"
#include "Simulation.h"
#include "Dataset_generator.h"
#include "helper.h"

// For debugging visualization TODO: remove later
#include "Graphic_viewer.h"

class Simulation_manager {
public:
    static void simulate_dataset (Movement movement_type, const std::vector<Asterism>& dataset);

    static void simulate_random_dataset (Movement movement_type);

    static void run_single_simulation (Movement movement_type, const Asterism& start, const Asterism& destination);

private:
    static void simulate_dataset_helper (Movement movement_type, const std::vector<Asterism>& dataset);
    static void simulate_dataset_outside_tech_field (const std::vector<Asterism>& dataset);
    static void print_results (const std::vector<Asterism>& dataset, Movement movement_type, int total_simulations, int successful_simulations, double durations_sum);
    static void insert_into_histogram (std::array<int, HISTOGRAM_INTERVALS_COUNT>& y_values, double value);
    static void print_histogram (const std::array<int, HISTOGRAM_INTERVALS_COUNT>& y_values);
};


#endif //ASTERISM_VALIDATOR_SIMULATION_MANAGER_H