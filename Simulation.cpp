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

void Simulation::run (Movement movement_type, const Asterism& movement_start, const Asterism& movement_destination) {
    switch (movement_type) {
        case Movement::linear:
            run_linear (movement_start, movement_destination);
            break;
        case Movement::safe_basic:
            run_safe_basic(movement_start, movement_destination);
            break;
        case Movement::outside_technical_field:
            run_outside_tech_field (movement_start);
            break;
        case Movement::A_star:
            run_A_star(movement_start, movement_destination);
            break;
        case Movement::none:
            std::cout << "Warning: attempted to run Simulation::run but movement type is 'none'" << std::endl;
            break;
    }
}

void Simulation::run_linear (const Asterism& movement_start, const Asterism& movement_destination) {
    reset_fields();
    type = Movement::linear;
    start = movement_start;
    destination = movement_destination;

    start_valid = start.is_valid();
    destination_valid = destination.is_valid();

    if ( !start_valid || !destination_valid ) {
        std::cout << "Warning: attempted to run Simulation::run_linear but start or destination asterism are not valid" << std::endl;
        return;
    }

    Board_set bs;
    bs.teleport_home();
    bs.assign_targets(start);
    bs.teleport(start);
    bs.assign_targets(destination);

    while (!bs.is_destination_reached(destination) && !collision_detected && iterations <= MAX_ITERATION_INDEX) {
        bs.step_move(destination);

        if (bs.detect_collision())
            collision_detected = true;
        if (bs.detect_vignette_fov_small())
            fov_small_vignette_detected = true;
        if (bs.detect_vignette_fov_large())
            fov_large_vignette_detected = true;

        iterations += 1;
    }

    duration = SIMULATION_TIME_STEP * iterations;

    if (bs.is_destination_reached(destination))
        destination_reached = true;
    distance_from_destination = bs.calculate_distance(destination);

    if (iterations > MAX_ITERATION_INDEX)
        max_iterations_exceeded = true;

}

void Simulation::run_safe_basic (const Asterism& movement_start, const Asterism& movement_destination) {
    reset_fields();
    type = Movement::safe_basic;
    start = movement_start;
    destination = movement_destination;

    start_valid = start.is_valid();
    destination_valid = destination.is_valid();

    if ( !start_valid || !destination_valid ) {
        std::cout << "Warning: attempted to run Simulation::run_safe_basic but start or destination asterism are not valid" << std::endl;
        return;
    }

    Board_set bs;
    bs.teleport_home();
    bs.assign_targets(start);
    bs.teleport(start);
    bs.assign_targets(destination);

    while (!bs.is_in_safe_zone() && !collision_detected && iterations <= MAX_ITERATION_INDEX) {
        bs.step_move_to_safe_zone();

        if (bs.detect_collision())
            collision_detected = true;
        if (bs.detect_vignette_fov_small())
            fov_small_vignette_detected = true;
        if (bs.detect_vignette_fov_large())
            fov_large_vignette_detected = true;

        iterations += 1;
    }

    while (!bs.is_destination_aligned_x(destination) && !collision_detected && iterations <= MAX_ITERATION_INDEX) {
        bs.step_move_along_x(destination);

        if (bs.detect_collision())
            collision_detected = true;
        if (bs.detect_vignette_fov_small())
            fov_small_vignette_detected = true;
        if (bs.detect_vignette_fov_large())
            fov_large_vignette_detected = true;

        iterations += 1;
    }

    while (!bs.is_destination_reached(destination, DESTINATION_REACHED_TOLERANCE * sqrt(2.)) && !collision_detected && iterations <= MAX_ITERATION_INDEX) {
        bs.step_move_along_y(destination);

        if (bs.detect_collision())
            collision_detected = true;
        if (bs.detect_vignette_fov_small())
            fov_small_vignette_detected = true;
        if (bs.detect_vignette_fov_large())
            fov_large_vignette_detected = true;

        iterations += 1;
    }

    duration = SIMULATION_TIME_STEP * iterations;

    if (bs.is_destination_reached(destination, DESTINATION_REACHED_TOLERANCE * sqrt(2.)))
        destination_reached = true;
    distance_from_destination = bs.calculate_distance(destination);

    if (iterations > MAX_ITERATION_INDEX)
        max_iterations_exceeded = true;
}

void Simulation::run_outside_tech_field (const Asterism& movement_start) {
    reset_fields();
    type = Movement::outside_technical_field;
    start = movement_start;

    start_valid = start.is_valid();

    if ( !start_valid ) {
        std::cout << "Warning: attempted to run Simulation::run_outside_tech_field but start asterism is not valid" << std::endl;
        return;
    }

    Board_set bs;
    bs.teleport_home();
    bs.assign_targets(start);
    bs.teleport(start);

    while (bs.is_in_technical_field() && !collision_detected && iterations <= MAX_ITERATION_INDEX) {
        bs.step_move_outside_tech_field();

        if (bs.detect_collision())
            collision_detected = true;
        if (bs.detect_vignette_fov_small())
            fov_small_vignette_detected = true;
        if (bs.detect_vignette_fov_large())
            fov_large_vignette_detected = true;

        iterations += 1;
    }

    duration = SIMULATION_TIME_STEP * iterations;

    if (!bs.is_in_technical_field()) {
        destination_reached = true;
        distance_from_destination = 0.;
    }

    if (iterations > MAX_ITERATION_INDEX)
        max_iterations_exceeded = true;
}

void Simulation::run_A_star (const Asterism& movement_start, const Asterism& movement_destination) {
    reset_fields();
    type = Movement::A_star;
    start = movement_start;
    destination = movement_destination;

    start_valid = start.is_valid();
    destination_valid = destination.is_valid();

    if ( !start_valid || !destination_valid ) {
        std::cout << "Warning: attempted to run Simulation::run_A_star but start or destination asterism are not valid" << std::endl;
        return;
    }

    State s = start;
    State d = destination;
    std::vector<State> path;

    if constexpr (GRID_TYPE == Grid_type::isometric) {
        if constexpr (FOV_OPTIONS == Fov_options::none)
            path = A_star::search_isometric (s, d, A_star::is_valid_state);
        else if constexpr (FOV_OPTIONS == Fov_options::fov_small_excluded)
            path = A_star::search_isometric (s, d, A_star::is_valid_state_fov_small_excluded);
        else if constexpr (FOV_OPTIONS == Fov_options::fov_large_excluded)
            path = A_star::search_isometric (s, d, A_star::is_valid_state_fov_large_excluded);
    }

    if constexpr (GRID_TYPE == Grid_type::manhattan) {
        if constexpr (FOV_OPTIONS == Fov_options::none)
            path = A_star::search_manhattan (s, d, A_star::is_valid_state);
        else if constexpr (FOV_OPTIONS == Fov_options::fov_small_excluded)
            path = A_star::search_manhattan (s, d, A_star::is_valid_state_fov_small_excluded);
        else if constexpr (FOV_OPTIONS == Fov_options::fov_large_excluded)
            path = A_star::search_manhattan (s, d, A_star::is_valid_state_fov_large_excluded);
    }

    if constexpr (GRID_TYPE == Grid_type::triangular) {
        if constexpr (FOV_OPTIONS == Fov_options::none)
            path = A_star::search_triangular (s, d, A_star::is_valid_state);
        else if constexpr (FOV_OPTIONS == Fov_options::fov_small_excluded)
            path = A_star::search_triangular (s, d, A_star::is_valid_state_fov_small_excluded);
        else if constexpr (FOV_OPTIONS == Fov_options::fov_large_excluded)
            path = A_star::search_triangular (s, d, A_star::is_valid_state_fov_large_excluded);
    }

    if (path.empty()) {
        std::cout << "Warning: attempted to run Simulation::run_A_star but no path was found" << std::endl;
        return;
    }

    Board_set bs;
    bs.teleport_home();
    bs.assign_targets(s);
    bs.teleport(s);
    bs.assign_targets(d);

    State current_destination;

    for (int i = 1; i < path.size(); ++i) {
        if (collision_detected)
            break;

        current_destination = path[i];

        while (!bs.is_destination_reached(current_destination) && !collision_detected && iterations <= MAX_ITERATION_INDEX) {
            bs.step_move(current_destination);

            if (bs.detect_collision())
                collision_detected = true;
            if (bs.detect_vignette_fov_small())
                fov_small_vignette_detected = true;
            if (bs.detect_vignette_fov_large())
                fov_large_vignette_detected = true;

            iterations += 1;
        }
    }

    while (!bs.is_destination_reached(d) && !collision_detected && iterations <= MAX_ITERATION_INDEX) {
        bs.step_move(d);

        if (bs.detect_collision())
            collision_detected = true;
        if (bs.detect_vignette_fov_small())
            fov_small_vignette_detected = true;
        if (bs.detect_vignette_fov_large())
            fov_large_vignette_detected = true;

        iterations += 1;
    }

    duration = SIMULATION_TIME_STEP * iterations;

    if (bs.is_destination_reached(d))
        destination_reached = true;
    distance_from_destination = bs.calculate_distance(d);

    if (iterations > MAX_ITERATION_INDEX)
        max_iterations_exceeded = true;
}

void Simulation::print_results () const {
    std::cout << std::endl;
    std::cout << "---------------------------------------------------------------------------------------------------------" << std::endl;

    switch ( type ) {
        case Movement::linear:
            std::cout << "> Movement type\t\t\t\tlinear" << std::endl;
            break;
        case Movement::outside_technical_field:
            std::cout << "> Movement type\t\t\t\toutside technical field" << std::endl;
            break;
        case Movement::safe_basic:
            std::cout << "> Movement type\t\t\t\tsafe basic" << std::endl;
            break;
        case Movement::A_star:
            std::cout << "> Movement type\t\t\t\tA star" << std::endl;
            break;
        case Movement::none:
            std::cout << "> Movement type\t\t\t\tnone" << std::endl;
            break;
    }

    std::cout << "> Start asterism\t\t\t";
    start.print();
    std::cout << "> Start valid\t\t\t\t" << (start_valid? "true":"false") << std::endl;

    std::cout << "> Destination asterism\t\t";
    destination.print();
    std::cout << "> Destination valid\t\t\t" << (destination_valid? "true":"false") << std::endl;

    std::cout << std::endl;
    std::cout << "> Boards cruise velocity\t" << BOARDS_CRUISE_VELOCITY << " mm/s" << std::endl;
    std::cout << "> Movement duration\t\t\t" << duration << " s" << std::endl;
    std::cout << "> Simulation iterations\t\t" << iterations << std::endl;
    std::cout << "> Max iterations exceeded\t" << (max_iterations_exceeded? "true":"false") << std::endl;
    std::cout << "> Simulation time step\t\t" << SIMULATION_TIME_STEP << " s" << std::endl;
    std::cout << "> Destination reached\t\t" << (destination_reached? "true":"false") << std::endl;
    std::cout << "> Distance from dest\t\t" << distance_from_destination << " mm" << std::endl;
    std::cout << "> Collision detected\t\t" << (collision_detected? "true":"false") << std::endl;
    std::cout << "> FoV small vignetting\t\t" << (fov_small_vignette_detected? "true":"false") << std::endl;
    std::cout << "> FoV large vignetting\t\t" << (fov_large_vignette_detected? "true":"false") << std::endl;
    std::cout << "---------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << std::endl << std::endl;
}

