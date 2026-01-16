#include <iostream>
#include "dataset.h"
#include "Board.h"
#include "Board_set.h"
#include "Simulation.h"

// int count_targets_detected (const Asterism& destination_asterism) {
//     Board_set temporary;
//     int count = 0;
//
//     if (temporary.board1.teleport(destination_asterism.ngs1) && temporary.board2.teleport(destination_asterism.ngs2) && temporary.board3.teleport(destination_asterism.ngs3) && !temporary.detect_collision())
//         count++;
//
//     if (temporary.board1.teleport(destination_asterism.ngs1) && temporary.board2.teleport(destination_asterism.ngs3) && temporary.board3.teleport(destination_asterism.ngs2) && !temporary.detect_collision())
//         count++;
//
//     if (temporary.board1.teleport(destination_asterism.ngs2) && temporary.board2.teleport(destination_asterism.ngs1) && temporary.board3.teleport(destination_asterism.ngs3) && !temporary.detect_collision())
//         count++;
//
//     if (temporary.board1.teleport(destination_asterism.ngs2) && temporary.board2.teleport(destination_asterism.ngs3) && temporary.board3.teleport(destination_asterism.ngs1) && !temporary.detect_collision())
//         count++;
//
//     if (temporary.board1.teleport(destination_asterism.ngs3) && temporary.board2.teleport(destination_asterism.ngs1) && temporary.board3.teleport(destination_asterism.ngs2) && !temporary.detect_collision())
//         count++;
//
//     if (temporary.board1.teleport(destination_asterism.ngs3) && temporary.board2.teleport(destination_asterism.ngs2) && temporary.board3.teleport(destination_asterism.ngs1) && !temporary.detect_collision())
//         count++;
//
//     return count;
// }

int main() {
    std::cout << std::fixed << std::setprecision(DECIMAL_PLACES_PRINTED);

    Board_set boards;
    Simulation simulation;

    int total_simulations = 0;
    int successful_simulations = 0;

    int count_over_80_seconds = 0;
    int count_over_100_seconds = 0;
    int count_over_120_seconds = 0;
    double durations_sum = 0.;

    for (int i = 1; i < dataset.size(); ++i) {
        simulation.run_linear_trajectory(boards, dataset[i-1], dataset[i]);
        total_simulations++;
        if (simulation.destination_reached && !simulation.collision_detected) {
            successful_simulations++;
            durations_sum += simulation.duration;
            if (simulation.duration > 80.) {
                count_over_80_seconds++;
                if (simulation.duration > 100.) {
                    count_over_100_seconds++;
                    if (simulation.duration > 120.)
                        count_over_120_seconds++;
                }
            }
        }
        else {
            std::cout << "Simulation from point " << i-1 << " to point " << i << " failed." << std::endl;
            simulation.print_results();
        }
    }

    std::cout << "Total simulations: " << total_simulations << std::endl;
    std::cout << "Successful simulations: " << successful_simulations << std::endl;
    std::cout << "Average duration of successful simulations: " << (durations_sum / successful_simulations) << " seconds" << std::endl;
    std::cout << "Number of successful simulations over 80 seconds: " << count_over_80_seconds << std::endl;
    std::cout << "Number of successful simulations over 100 seconds: " << count_over_100_seconds << std::endl;
    std::cout << "Number of successful simulations over 120 seconds: " << count_over_120_seconds << std::endl;

    return 0;

    // boards.assign_targets(dataset[73]);
    // boards.teleport(dataset[73]);
    // boards.draw(dataset[73]);
    // boards.draw(dataset[74]);
    //
    // simulation.run_linear_trajectory(boards, dataset[73], dataset[74]);
    // simulation.print_results();
    //
    // boards.assign_targets(dataset[170]);
    // boards.teleport(dataset[170]);
    // boards.draw(dataset[170]);
    // boards.draw(dataset[171]);
    //
    // simulation.run_linear_trajectory(boards, dataset[170], dataset[171]);
    // simulation.print_results();

}