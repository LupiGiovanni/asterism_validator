//
// Created by gionimbus on 1/7/26.
//

#include "Simulation.h"

Simulation::Simulation() {
    reset_fields();
}

void Simulation::reset_fields () {
    type = Movement::none;
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

bool Simulation::is_start_valid () const {
    return start_valid;
}

bool Simulation::is_destination_valid () const {
    return destination_valid;
}

bool Simulation::is_destination_reached () const {
    return destination_reached;
}

bool Simulation::is_collision_detected () const {
    return collision_detected;
}

double Simulation::get_duration() const {
    return duration;
}

void Simulation::run (Movement movement_type, Board_set& board_set, const Asterism& movement_start, const Asterism& movement_destination) {
    switch (movement_type) {
        case Movement::linear_trajectory:
            run_linear_trajectory (board_set, movement_start, movement_destination);
            break;
        case Movement::outside_technical_field:
            run_outside_tech_field (board_set, movement_start);
            break;
        case Movement::none:
            std::cout << "Warning: movement type is none" << std::endl;
            break;
    }
}

void Simulation::run_linear_trajectory (Board_set& board_set, const Asterism& trajectory_start, const Asterism& trajectory_destination) {
    reset_fields();
    type = Movement::linear_trajectory;
    start = trajectory_start;
    destination = trajectory_destination;

    board_set.assign_targets(start);
    if ( ! board_set.get_targets().empty() ) {
        start_valid = true;
        board_set.teleport(start);
    }

    board_set.assign_targets(destination);
    if ( ! board_set.get_targets().empty() )
        destination_valid = true;

    if ( start_valid && destination_valid ) {
        while ( ! board_set.is_destination_reached(destination) && ! collision_detected && iterations <= MAX_ITERATION_INDEX ) {
            board_set.move(destination, SIMULATION_DISTANCE_STEP);
            collision_detected = board_set.detect_collision();

            if ( board_set.detect_vignette_fov_small() )
                fov_small_vignette_detected = true;
            if ( board_set.detect_vignette_fov_large() )
                fov_large_vignette_detected = true;

            iterations += 1;
        }

        duration = SIMULATION_TIME_STEP * iterations;

        if ( board_set.is_destination_reached(destination) ) {
            destination_reached = true;
            distance_from_destination = board_set.calculate_distance(destination);
        }

        if (iterations > MAX_ITERATION_INDEX)
            max_iterations_exceeded = true;
    }
    else
        std::cout << "Warning: attempted to run linear trajectory simulation but start or destination asterism are not valid" << std::endl;
}

void Simulation::run_outside_tech_field (Board_set& board_set, const Asterism& movement_start) {
    reset_fields();
    type = Movement::outside_technical_field;
    start = movement_start;

    board_set.assign_targets(start);
    if ( ! board_set.get_targets().empty() ) {
        start_valid = true;
        board_set.teleport(start);
    }

    if ( start_valid ) {
        while ( board_set.is_in_technical_field() && ! collision_detected && iterations <= MAX_ITERATION_INDEX ) {
            board_set.move_outside_tech_field(SIMULATION_DISTANCE_STEP);
            collision_detected = board_set.detect_collision();

            if (board_set.detect_vignette_fov_small())
                fov_small_vignette_detected = true;
            if (board_set.detect_vignette_fov_large())
                fov_large_vignette_detected = true;

            iterations += 1;
        }

        duration = SIMULATION_TIME_STEP * iterations;

        if ( ! board_set.is_in_technical_field() ) {
            destination_reached = true;
            distance_from_destination = 0.;
        }

        if (iterations > MAX_ITERATION_INDEX)
            max_iterations_exceeded = true;

    }
    else
        std::cout << "Warning: attempted to run outside-technical-field movement simulation but start asterism is not valid" << std::endl;
}

void Simulation::print_results() const {
    std::cout << std::endl;
    std::cout << "======================================================================================" << std::endl;
    std::cout << "                              Single simulation results                               " << std::endl;
    std::cout << std::endl;

    switch ( type ) {
        case Movement::linear_trajectory:
            std::cout << "> Movement type\t\t\t\tlinear trajectory" << std::endl;
            break;
        case Movement::outside_technical_field:
            std::cout << "> Movement type\t\t\t\toutside technical field" << std::endl;
            break;
        case Movement::none:
            std::cout << "> Movement type\t\t\t\tnone" << std::endl;
            break;
    }

    std::cout << "> Start asterism\t\t\t";
    start.print();
    std::cout << std::endl;
    std::cout << "> Start valid\t\t\t\t" << (start_valid? "true":"false") << std::endl;

    std::cout << "> Destination asterism\t\t";
    destination.print();
    std::cout << std::endl;
    std::cout << "> Destination valid\t\t\t" << (destination_valid? "true":"false") << std::endl;

    std::cout << std::endl;
    std::cout << "> Boards cruise velocity\t" << BOARD_VELOCITY << " mm/s" << std::endl;
    std::cout << "> Movement duration\t\t\t" << duration << " seconds" << std::endl;
    std::cout << "> Simulation iterations\t\t" << iterations << std::endl;
    std::cout << "> Max iterations exceeded\t" << (max_iterations_exceeded? "true":"false") << std::endl;
    std::cout << "> Iteration time step\t\t" << SIMULATION_TIME_STEP << " seconds" << std::endl;
    std::cout << "> Iteration distance step\t" << SIMULATION_DISTANCE_STEP << " mm" << std::endl;
    std::cout << "> Destination reached\t\t" << (destination_reached? "true":"false") << std::endl;
    std::cout << "> Distance from dest\t\t" << distance_from_destination << std::endl;
    std::cout << "> Collision detected\t\t" << (collision_detected? "true":"false") << std::endl;
    std::cout << "> FoV small vignetting\t\t" << (fov_small_vignette_detected? "true":"false") << std::endl;
    std::cout << "> FoV large vignetting\t\t" << (fov_large_vignette_detected? "true":"false") << std::endl;
    std::cout << "======================================================================================" << std::endl;
    std::cout << std::endl;
}

