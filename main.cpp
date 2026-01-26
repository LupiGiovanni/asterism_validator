#include "Asterism.h"
#include "Board.h"
#include "Board_set.h"
#include "Simulation.h"
#include "helper.h"
#include "dataset.h"

void dataset_simulation_linear_trajectory(const std::vector<Asterism>& dataset) {
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
}

void dataset_outside_tech_field(const std::vector<Asterism>& dataset) {
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
    std::cout << std::endl << std::endl;
}

int main () {
    dataset_simulation_linear_trajectory(cedric_dataset);
    //dataset_outside_tech_field(cedric_dataset);
}