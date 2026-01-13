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

    // int total_simulations = 0;
    // int successful_simulations = 0;
    //
    // for (int i = 1; i < dataset.size(); ++i) {
    //     simulation.linear_trajectory(boards, dataset[i-1], dataset[i]);
    //     total_simulations++;
    //     if (simulation.destination_reached && !simulation.collision_detected)
    //         successful_simulations++;
    //     else {
    //         std::cout << "Simulation from point " << i-1 << " to point " << i << " failed." << std::endl;
    //         simulation.print_results();
    //     }
    // }
    //
    // std::cout << "Total simulations: " << total_simulations << std::endl;
    // std::cout << "Successful simulations: " << successful_simulations << std::endl;

    boards.teleport(dataset[170]);
    boards.draw(dataset[170]);
    boards.draw(dataset[171]);
    simulation.run_linear_trajectory(boards, dataset[170], dataset[171]);
    simulation.print_results();
    return 0;
}