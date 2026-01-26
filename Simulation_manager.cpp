//
// Created by gionimbus on 1/26/26.
//

#include "Simulation_manager.h"

void Simulation_manager::simulate_dataset (Movement movement_type, const std::vector<Asterism>& dataset) {
    switch ( movement_type ) {
        case Movement::linear_trajectory:
            simulate_dataset_linear_trajectory(dataset);
            break;
        case Movement::outside_technical_field:
            simulate_dataset_outside_tech_field(dataset);
            break;
        case Movement::none:
            std::cout << "Warning: attempted to run dataset simulation but 'movement_type' is 'none'" << std::endl;
            break;
    }
}

void Simulation_manager::simulate_random_dataset(Movement movement_type) {
    Dataset_generator dg;
    dg.generate_random_valid_dataset();
    simulate_dataset(movement_type, dg.get_dataset());
}

void Simulation_manager::simulate_dataset_linear_trajectory(const std::vector<Asterism> &dataset) {
    if ( dataset.empty() ) {
        std::cout << "Warning: attempted to run dataset simulation but 'dataset' vector is empty" << std::endl;
        return;
    }

    std::cout << std::fixed << std::setprecision(DECIMAL_PLACES_PRINTED);

    Board_set boards;
    Simulation simulation;

    int total_simulations = 0;
    int successful_simulations = 0;
    double durations_sum = 0.;

    for (int i = 1; i < dataset.size(); ++i) {
        simulation.run(Movement::linear_trajectory,boards, dataset[i-1], dataset[i]);
        total_simulations++;
        if (simulation.is_destination_reached() && !simulation.is_collision_detected()) {
            successful_simulations++;
            durations_sum += simulation.get_duration();
        }
        else if (simulation.is_start_valid() && simulation.is_destination_valid()) {
            std::cout << "Simulation from point " << i-1 << " to point " << i << " failed." << std::endl;
            simulation.print_results();
        }
    }

    std::cout << "Total simulations: " << total_simulations << std::endl;
    std::cout << "Successful simulations: " << successful_simulations << std::endl;
    std::cout << "Average duration of successful simulations: " << (durations_sum / successful_simulations) << " seconds" << std::endl;
    std::cout << std::endl;
}

void Simulation_manager::simulate_dataset_outside_tech_field(const std::vector<Asterism> &dataset) {
    if ( dataset.empty() ) {
        std::cout << "Warning: attempted to run dataset simulation but 'dataset' vector is empty" << std::endl;
        return;
    }

    std::cout << std::fixed << std::setprecision(DECIMAL_PLACES_PRINTED);

    Board_set boards;
    Simulation simulation;

    int total_simulations = 0;
    int successful_simulations = 0;
    double durations_sum = 0.;

    for (int i = 0; i < dataset.size(); ++i) {
        simulation.run(Movement::outside_technical_field, boards, dataset[i]);
        total_simulations++;
        if (simulation.is_destination_reached() && !simulation.is_collision_detected()) {
            successful_simulations++;
            durations_sum += simulation.get_duration();
        }
        else if (simulation.is_start_valid()) {
            std::cout << "Simulation from point " << i << " failed." << std::endl;
            simulation.print_results();
        }
    }

    std::cout << "Total simulations: " << total_simulations << std::endl;
    std::cout << "Successful simulations: " << successful_simulations << std::endl;
    std::cout << "Average duration of successful simulations: " << (durations_sum / successful_simulations) << " seconds" << std::endl;
    std::cout << std::endl;
}
