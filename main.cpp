#include <iostream>
#include "dataset.h"
#include "Board.h"
#include "Board_set.h"
#include "Simulation.h"

int count_targets_detected (const Asterism& destination_asterism) {
    Board_set temporary;
    int count = 0;

    if (temporary.board1.teleport(destination_asterism.ngs1) && temporary.board2.teleport(destination_asterism.ngs2) && temporary.board3.teleport(destination_asterism.ngs3) && !temporary.detect_collision())
        count++;

    if (temporary.board1.teleport(destination_asterism.ngs1) && temporary.board2.teleport(destination_asterism.ngs3) && temporary.board3.teleport(destination_asterism.ngs2) && !temporary.detect_collision())
        count++;

    if (temporary.board1.teleport(destination_asterism.ngs2) && temporary.board2.teleport(destination_asterism.ngs1) && temporary.board3.teleport(destination_asterism.ngs3) && !temporary.detect_collision())
        count++;

    if (temporary.board1.teleport(destination_asterism.ngs2) && temporary.board2.teleport(destination_asterism.ngs3) && temporary.board3.teleport(destination_asterism.ngs1) && !temporary.detect_collision())
        count++;

    if (temporary.board1.teleport(destination_asterism.ngs3) && temporary.board2.teleport(destination_asterism.ngs1) && temporary.board3.teleport(destination_asterism.ngs2) && !temporary.detect_collision())
        count++;

    if (temporary.board1.teleport(destination_asterism.ngs3) && temporary.board2.teleport(destination_asterism.ngs2) && temporary.board3.teleport(destination_asterism.ngs1) && !temporary.detect_collision())
        count++;

    return count;
}

void dataset_run_simulation_linear_trajectory() {
    std::cout << std::fixed << std::setprecision(DECIMAL_PLACES_PRINTED);

    Board_set boards;
    Simulation simulation;

    int total_simulations = 0;
    int successful_simulations = 0;
    double durations_sum = 0.;

    for (int i = 1; i < dataset.size(); ++i) {
        simulation.run_linear_trajectory(boards, dataset[i-1], dataset[i]);
        total_simulations++;
        if (simulation.destination_reached && !simulation.collision_detected) {
            successful_simulations++;
            durations_sum += simulation.duration;
        }
        else {
            std::cout << "Simulation from point " << i-1 << " to point " << i << " failed." << std::endl;
            simulation.print_results();
        }
    }

    std::cout << "Total simulations: " << total_simulations << std::endl;
    std::cout << "Successful simulations: " << successful_simulations << std::endl;
    std::cout << "Average duration of successful simulations: " << (durations_sum / successful_simulations) << " seconds" << std::endl;
}

void dataset_run_simulation_out_of_technical_field_y_neg() {
    std::cout << std::fixed << std::setprecision(DECIMAL_PLACES_PRINTED);

    Board_set boards;
    Simulation simulation;

    int total_simulations = 0;
    int successful_simulations = 0;
    int successful_over_10_seconds = 0;
    int successful_over_20_seconds = 0;
    int successful_over_30_seconds = 0;
    int successful_over_40_seconds = 0;
    double durations_sum = 0.;

    for (int i = 0; i < dataset.size(); ++i) {
        simulation.run_out_of_technical_field_y_neg(boards, dataset[i]);
        total_simulations++;
        if (simulation.destination_reached && !simulation.collision_detected) {
            successful_simulations++;
            durations_sum += simulation.duration;
            if (simulation.duration > 10.)
                successful_over_10_seconds++;
                if (simulation.duration > 20.)
                    successful_over_20_seconds++;
                    if (simulation.duration > 30.)
                        successful_over_30_seconds++;
                        if (simulation.duration > 40.)
                            successful_over_40_seconds++;
        }
        else {
            std::cout << "Simulation from point " << i << " failed." << std::endl;
            simulation.print_results();
        }
    }

    std::cout << "Total simulations: " << total_simulations << std::endl;
    std::cout << "Successful simulations: " << successful_simulations << std::endl;
    std::cout << "Average duration of successful simulations: " << (durations_sum / successful_simulations) << " seconds" << std::endl;
    std::cout << "Successful simulations over 10 seconds: " << successful_over_10_seconds << std::endl;
    std::cout << "Successful simulations over 20 seconds: " << successful_over_20_seconds << std::endl;
    std::cout << "Successful simulations over 30 seconds: " << successful_over_30_seconds << std::endl;
    std::cout << "Successful simulations over 40 seconds: " << successful_over_40_seconds << std::endl;
    std::cout << std::endl;
}

void dataset_run_simulation_out_of_technical_field_corner() {
    std::cout << std::fixed << std::setprecision(DECIMAL_PLACES_PRINTED);

    Board_set boards;
    Simulation simulation;

    int total_simulations = 0;
    int successful_simulations = 0;
    int successful_over_10_seconds = 0;
    int successful_over_20_seconds = 0;
    int successful_over_30_seconds = 0;
    int successful_over_40_seconds = 0;
    double durations_sum = 0.;

    for (int i = 0; i < dataset.size(); ++i) {
        simulation.run_out_of_technical_field_corner(boards, dataset[i]);
        total_simulations++;
        if (simulation.destination_reached && !simulation.collision_detected) {
            successful_simulations++;
            durations_sum += simulation.duration;
            if (simulation.duration > 10.)
                successful_over_10_seconds++;
                if (simulation.duration > 20.)
                    successful_over_20_seconds++;
                    if (simulation.duration > 30.)
                        successful_over_30_seconds++;
                        if (simulation.duration > 40.)
                            successful_over_40_seconds++;
        }
        else {
            std::cout << "Simulation from point " << i << " failed." << std::endl;
            simulation.print_results();
        }
    }

    std::cout << "Total simulations: " << total_simulations << std::endl;
    std::cout << "Successful simulations: " << successful_simulations << std::endl;
    std::cout << "Average duration of successful simulations: " << (durations_sum / successful_simulations) << " seconds" << std::endl;
    std::cout << "Successful simulations over 10 seconds: " << successful_over_10_seconds << std::endl;
    std::cout << "Successful simulations over 20 seconds: " << successful_over_20_seconds << std::endl;
    std::cout << "Successful simulations over 30 seconds: " << successful_over_30_seconds << std::endl;
    std::cout << "Successful simulations over 40 seconds: " << successful_over_40_seconds << std::endl;
    std::cout << std::endl;
}

int main() {
    dataset_run_simulation_out_of_technical_field_y_neg();
    return 0;
}