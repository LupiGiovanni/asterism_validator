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
    start_valid = false;
    destination = zero_asterism;
    destination_valid = false;
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
    if (boards.get_targets() != Board_set_targets::none) {
        start_valid = true;
        boards.teleport(start);
    }

    boards.assign_targets(destination);
    if (boards.get_targets() != Board_set_targets::none)
        destination_valid = true;

    if (start_valid && destination_valid) {
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
    } else
        std::cout << "Warning: attempted to run simulation but start asterism or destination asterism are not valid" << std::endl;

    return false;
}

bool Simulation::run_out_of_technical_field (Board_set& boards, const Asterism& movement_start) {
    reset_result_fields();
    type = Movement_type::out_of_technical_field;
    start = movement_start;

    boards.assign_targets(start);
    if (boards.get_targets() != Board_set_targets::none) {
        start_valid = true;
        boards.teleport(start);
    }

    if (start_valid) {
        while (boards.is_in_technical_field() && !collision_detected && iterations <= MAX_ITERATION_INDEX) {
            // boards.draw(start);
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
    } else
        std::cout << "Warning: attempted to run simulation but start asterism is not valid" << std::endl;

    return false;
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
        case Movement_type::out_of_technical_field:
            std::cout << "> Movement type\t\t\t\tout of technical field" << std::endl;
            break;
        case Movement_type::none:
            std::cout << "> Movement type\t\t\t\tnone" << std::endl;
            break;
    }

    std::cout << "> Start asterism\t\t\t";
    start.print();
    std::cout << std::endl;
    std::cout << "> Start valid\t\t\t\t" << ((start_valid)? ("true"):("false")) << std::endl;

    std::cout << "> Destination asterism\t\t";
    destination.print();
    std::cout << std::endl;
    std::cout << "> Destination valid\t\t\t" << ((destination_valid)? ("true"):("false")) << std::endl;

    std::cout << std::endl;
    std::cout << "> Movement duration\t\t\t" << duration << " seconds" << std::endl;
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

bool Simulation::is_destination_reached () const {
    return destination_reached;
}

double Simulation::get_duration () const {
    return duration;
}

bool Simulation::is_start_valid () const {
    return start_valid;
}

bool Simulation::is_destination_valid () const {
    return destination_valid;
}

bool Simulation::is_collision_detected () const {
    return collision_detected;
}

