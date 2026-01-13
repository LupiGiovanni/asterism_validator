//
// Created by gionimbus on 1/7/26.
//

#include <iostream>
#include <iomanip>
#include "Simulation.h"


Simulation::Simulation () {
    reset_result_fields();
}

void Simulation::reset_result_fields () {
    type = Trajectory_type::none;
    Asterism zero_asterism;
    start = zero_asterism;
    destination = zero_asterism;
    destination_reached = false;
    collision_detected = false;
    fov_small_vignette_detected = false;
    fov_large_vignette_detected = false;
    duration = 0.;
    iterations = 0;
    max_iterations_exceeded = false;
}

bool Simulation::run_linear_trajectory(Board_set& boards, const Asterism& trajectory_start, const Asterism& trajectory_destination) {
    reset_result_fields();
    type = Trajectory_type::linear_trajectory;
    start = trajectory_start;
    destination = trajectory_destination;

    boards.teleport(start);
    boards.assign_ngs(destination);

    while (!boards.is_destination_reached(destination) && !collision_detected && iterations <= MAX_ITERATION_INDEX) {
        boards.move_step_linear(destination, SIMULATION_DISTANCE_STEP);
        collision_detected = boards.detect_collision();
        if (boards.detect_vignette_fov_small())
            fov_small_vignette_detected = true;
        if (boards.detect_vignette_fov_large())
            fov_large_vignette_detected = true;
        iterations += 1;
    }

    duration = SIMULATION_TIME_STEP * iterations;

    if (boards.is_destination_reached(destination)) {
        destination_reached = true;
        return true;
    }

    if (iterations > MAX_ITERATION_INDEX) {
        max_iterations_exceeded = true;
    }

    return false;
}

void Simulation::print_results() const {
    std::cout << std::endl;
    std::cout << "======================================================================================" << std::endl;
    std::cout << "                                Simulation results                                    " << std::endl;
    std::cout << std::endl;

    switch (type){
        case Trajectory_type::linear_trajectory:
            std::cout << "> Trajectory type\t\t\tlinear trajectory" << std::endl;
            break;
        case Trajectory_type::non_linear_trajectory:
            std::cout << "> Trajectory type\t\t\tnon-linear trajectory" << std::endl;
            break;
        case Trajectory_type::none:
            std::cout << "> Trajectory type\t\t\tnone" << std::endl;
            break;
    }

    std::cout << "> Start asterism\t\t\t";
    start.print();
    std::cout << std::endl;

    std::cout << "> Destination asterism\t\t";
    destination.print();
    std::cout << std::endl;

    std::cout << "> Trajectory duration\t\t" << duration << " seconds" << std::endl;
    std::cout << "> Simulation iterations\t\t" << iterations << std::endl;
    std::cout << "> Max iterations exceeded\t" << ((max_iterations_exceeded)? ("true"):("false")) << std::endl;
    std::cout << "> Iteration time step\t\t" << SIMULATION_TIME_STEP << " seconds" << std::endl;
    std::cout << "> Iteration distance step\t" << SIMULATION_DISTANCE_STEP << " mm" << std::endl;
    std::cout << "> Destination reached\t\t" << ((destination_reached)? ("true"):("false")) << std::endl;
    std::cout << "> Collision detected\t\t" << ((collision_detected)? ("true"):("false")) << std::endl;
    std::cout << "> FoV small vignetting\t\t" << ((fov_small_vignette_detected)? ("true"):("false")) << std::endl;
    std::cout << "> FoV large vignetting\t\t" << ((fov_large_vignette_detected)? ("true"):("false")) << std::endl;
    std::cout << "======================================================================================" << std::endl;
    std::cout << std::endl;
}

