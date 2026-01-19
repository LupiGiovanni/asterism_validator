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
    type = Movement_type::none;
    Asterism zero_asterism;
    start = zero_asterism;
    destination = zero_asterism;
    destination_reached = false;
    distance_from_destination = std::numeric_limits<double>::infinity();
    collision_detected = false;
    fov_small_vignette_detected = false;
    fov_large_vignette_detected = false;
    duration = 0.;
    iterations = 0;
    max_iterations_exceeded = false;
}

bool Simulation::run_linear_trajectory (Board_set& boards, const Asterism& trajectory_start, const Asterism& trajectory_destination) {
    reset_result_fields();
    type = Movement_type::linear_trajectory;
    start = trajectory_start;
    destination = trajectory_destination;

    boards.assign_targets(start);
    boards.teleport(start);
    boards.assign_targets(destination);

    while (!boards.is_destination_reached(destination) && !collision_detected && iterations <= MAX_ITERATION_INDEX) {
        // boards.draw(destination);
        boards.move_step_linear_trajectory(destination, SIMULATION_DISTANCE_STEP);
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
        distance_from_destination = boards.calculate_distance(destination);
        return true;
    }

    if (iterations > MAX_ITERATION_INDEX) {
        max_iterations_exceeded = true;
    }

    return false;
}

bool Simulation::run_out_of_technical_field_y_neg (Board_set& boards, const Asterism& movement_start) {
    return run_out_of_technical_field_helper(boards, movement_start, Movement_type::out_of_technical_field_y_neg);
}

bool Simulation::run_out_of_technical_field_corner (Board_set& boards, const Asterism& movement_start) {
    return run_out_of_technical_field_helper(boards, movement_start, Movement_type::out_of_technical_field_corner);
}

void Simulation::print_results() const {
    std::cout << std::endl;
    std::cout << "======================================================================================" << std::endl;
    std::cout << "                                Simulation results                                    " << std::endl;
    std::cout << std::endl;

    switch (type){
        case Movement_type::linear_trajectory:
            std::cout << "> Movement type\t\t\t\tlinear trajectory" << std::endl;
            break;
        case Movement_type::non_linear_trajectory:
            std::cout << "> Movement type\t\t\t\tnon-linear trajectory" << std::endl;
            break;
        case Movement_type::out_of_technical_field_y_neg:
            std::cout << "> Movement type\t\t\t\tout of technical field y negative" << std::endl;
            break;
        case Movement_type::out_of_technical_field_corner:
            std::cout << "> Movement type\t\t\t\tout of technical field corner" << std::endl;
            break;
        case Movement_type::none:
            std::cout << "> Movement type\t\t\t\tnone" << std::endl;
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
    std::cout << "> Distance from dest\t\t" << distance_from_destination << std::endl;
    std::cout << "> Collision detected\t\t" << ((collision_detected)? ("true"):("false")) << std::endl;
    std::cout << "> FoV small vignetting\t\t" << ((fov_small_vignette_detected)? ("true"):("false")) << std::endl;
    std::cout << "> FoV large vignetting\t\t" << ((fov_large_vignette_detected)? ("true"):("false")) << std::endl;
    std::cout << "======================================================================================" << std::endl;
    std::cout << std::endl;
}

bool Simulation::run_out_of_technical_field_helper(Board_set& boards, const Asterism& movement_start, const Movement_type movement_type) {
    reset_result_fields();
    type = movement_type;
    start = movement_start;

    boards.assign_targets(start);
    boards.teleport(start);

    while (boards.is_in_technical_field() && !collision_detected && iterations <= MAX_ITERATION_INDEX) {
        // boards.draw(start);

        if (movement_type == Movement_type::out_of_technical_field_y_neg)
            boards.move_step_out_of_technical_field_y_neg(SIMULATION_DISTANCE_STEP);
        else if (movement_type == Movement_type::out_of_technical_field_corner)
            boards.move_step_out_of_technical_field_corner(SIMULATION_DISTANCE_STEP);

        collision_detected = boards.detect_collision();
        if (boards.detect_vignette_fov_small())
            fov_small_vignette_detected = true;
        if (boards.detect_vignette_fov_large())
            fov_large_vignette_detected = true;

        iterations += 1;
    }

    duration = SIMULATION_TIME_STEP * iterations;

    if (!boards.is_in_technical_field()) {
        destination_reached = true;
        distance_from_destination = 0.;
        return true;
    }

    if (iterations > MAX_ITERATION_INDEX) {
        max_iterations_exceeded = true;
    }

    return false;
}

