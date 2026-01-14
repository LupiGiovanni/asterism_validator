#include <iostream>
#include "dataset.h"
#include "global_functions.h"
#include "Board.h"
#include "Board_set.h"
#include "Asterism.h"
#include "Simulation.h"

int main() {
    Board_set boards;
    Simulation simulation;

    int total_simulations = 0;
    int successful_simulations = 0;

    for (int i = 1; i < dataset.size(); ++i) {
        boards.set_current_asterism(dataset[i]);
        boards.calculate_valid_permutations();
        boards.order_valid_permutations_by_distance();
        for (const auto& it: boards.valid_permutations)
            simulation.run_linear_trajectory(boards, dataset[i-1], it);
        total_simulations++;
        if (simulation.destination_reached && !simulation.collision_detected)
            successful_simulations++;
        else {
            std::cout << "Simulation from point " << i-1 << " to point " << i << " failed." << std::endl;
            simulation.print_results();
        }
    }

    std::cout << "Total simulations: " << total_simulations << std::endl;
    std::cout << "Successful simulations: " << successful_simulations << std::endl;

    // boards.set_current_asterism (dataset[0]);
    // boards.calculate_valid_permutations ();
    // boards.order_valid_permutations_by_distance();
    // std::cout << "Valid permutations for the first dataset point:" << std::endl;
    // for (const auto& it: boards.valid_permutations) {
    //     it.print();
    //     std::cout << std::endl;
    // }
    //
    // boards.set_current_asterism(dataset[1]);
    // boards.calculate_valid_permutations();
    // boards.order_valid_permutations_by_distance();
    // std::cout << "Valid permutations for the second dataset point:" << std::endl;
    // for (const auto& it: boards.valid_permutations) {
    //     it.print();
    //     std::cout << std::endl;
    // }
    //
    // boards.set_current_asterism(dataset[2]);
    // boards.calculate_valid_permutations();
    // boards.order_valid_permutations_by_distance();
    // std::cout << "Valid permutations for the third dataset point:" << std::endl;
    // for (const auto& it: boards.valid_permutations) {
    //     it.print();
    //     std::cout << std::endl;
    // }
    //
    // boards.set_current_asterism(dataset[3]);
    // boards.calculate_valid_permutations();
    // boards.order_valid_permutations_by_distance();
    // std::cout << "Valid permutations for the fourth dataset point:" << std::endl;
    // for (const auto& it: boards.valid_permutations) {
    //     it.print();
    //     std::cout << std::endl;
    // }

    return 0;
}