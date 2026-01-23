//
// Created by gionimbus on 12/16/25.
//

#ifndef ASTERISM_VALIDATOR_HELPER_H
#define ASTERISM_VALIDATOR_HELPER_H

#include <CGAL/Aff_transformation_2.h>

#include "Asterism.h"
#include "Board.h"
#include "Board_set.h"
#include "Simulation.h"

typedef CGAL::Aff_transformation_2<Kernel> Transformation;

// Number of decimal places used to print double values
constexpr int DECIMAL_PLACES_PRINTED = 6;


// Rotates polygon in anti-clockwise direction by angle_radians. The center of rotation is the origin of the
// coordinates system
inline void rotate (Polygon& polygon, double angle_radians) {
    Transformation rotation (CGAL::ROTATION, std::sin(angle_radians), std::cos(angle_radians));
    for (auto& vertex : polygon)
        vertex = rotation.transform(vertex);
}

// Same as previous method but takes a point as argument
inline void rotate (Point& point, double angle_radians) {
    Transformation rotation (CGAL::ROTATION, std::sin(angle_radians), std::cos(angle_radians));
    point = rotation.transform(point);
}

inline void dataset_run_simulation_linear_trajectory(const std::vector<Asterism>& dataset) {
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
        else if (simulation.start_valid && simulation.destination_valid) {
            std::cout << "Simulation from point " << i-1 << " to point " << i << " failed." << std::endl;
            simulation.print_results();
        }
    }

    std::cout << "Total simulations: " << total_simulations << std::endl;
    std::cout << "Successful simulations: " << successful_simulations << std::endl;
    std::cout << "Average duration of successful simulations: " << (durations_sum / successful_simulations) << " seconds" << std::endl;
}

inline int count_targets_detected (const Asterism& destination_asterism) {
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

inline void dataset_run_simulation_out_of_technical_field(const std::vector<Asterism>& dataset) {
    std::cout << std::fixed << std::setprecision(DECIMAL_PLACES_PRINTED);

    Board_set boards;
    Simulation simulation;

    int total_simulations = 0;
    int successful_simulations = 0;
    double durations_sum = 0.;

    for (int i = 0; i < dataset.size(); ++i) {
        simulation.run_out_of_technical_field(boards, dataset[i]);
        total_simulations++;
        if (simulation.destination_reached && !simulation.collision_detected) {
            successful_simulations++;
            durations_sum += simulation.duration;
        }
        else if (simulation.start_valid) {
            std::cout << "Simulation from point " << i << " failed." << std::endl;
            simulation.print_results();
        }
    }

    std::cout << "Total simulations: " << total_simulations << std::endl;
    std::cout << "Successful simulations: " << successful_simulations << std::endl;
    std::cout << "Average duration of successful simulations: " << (durations_sum / successful_simulations) << " seconds" << std::endl;
    std::cout << std::endl << std::endl;
}

#endif //ASTERISM_VALIDATOR_HELPER_H