//
// Created by gionimbus on 1/7/26.
//

#include "Simulation.h"

Simulation::Simulation ():  type(Simulation_type::none),
                            start(Asterism(0.,0.,0.,0.,0.,0.)),
                            destination(Asterism(0.,0.,0.,0.,0.,0.)),
                            destination_reached(false),
                            collision_detected(false),
                            fov_small_vignette_detected(false),
                            fov_large_vignette_detected(false),
                            duration(0.){}

bool Simulation::linear_trajectory(Board_set& boards, const Asterism& trajectory_start, const Asterism& trajectory_destination) {
    type = Simulation_type::linear_trajectory;
    start = trajectory_start;
    destination = trajectory_destination;
    int time_index = 0;
    collision_detected = false;
    fov_small_vignette_detected = false;
    fov_large_vignette_detected = false;

    boards.teleport(start);

    while (!boards.is_reached(destination) && !collision_detected && time_index <= MAX_TIME_INDEX) {
        boards.move_step_linear(destination, SIMULATION_DISTANCE_STEP);
        collision_detected = boards.detect_collision();
        if (boards.detect_vignette_fov_small())
            fov_small_vignette_detected = true;
        if (boards.detect_vignette_fov_large())
            fov_large_vignette_detected = true;
        time_index += 1;
    }

    duration = SIMULATION_TIME_STEP * time_index;

    if (boards.is_reached(destination)) {
        destination_reached = true;
        return true;
    }

    if (time_index > MAX_TIME_INDEX) {
        std::cout << "Simulation error: max time index exceeded." << std::endl;
    }

    return false;
}

void Simulation::print_results() const {
    std::cout << "==================== Simulation Results ====================" << std::endl;
    switch (type){
        case Simulation_type::linear_trajectory:
            std::cout << "> Simulation type\t\tlinear trajectory" << std::endl;
            break;
        case Simulation_type::non_linear_trajectory:
            std::cout << "> Simulation type\t\tnon-linear trajectory" << std::endl;
            break;
        case Simulation_type::none:
            std::cout << "> Simulation type\t\tnone" << std::endl;
            break;
    }

    std::cout << "> Start asterism\t\t";
    start.print();
    std::cout << std::endl;

    std::cout << "> Destination asterism\t";
    destination.print();
    std::cout << std::endl;

    std::cout << "> Simulation duration\t" << duration << " seconds" << std::endl;
    std::cout << "> Destination reached\t" << ((destination_reached)? ("true"):("false")) << std::endl;
    std::cout << "> Collision detected\t" << ((collision_detected)? ("true"):("false")) << std::endl;
    std::cout << "> FoV small vignetting\t" << ((fov_small_vignette_detected)? ("true"):("false")) << std::endl;
    std::cout << "> FoV large vignetting\t" << ((fov_large_vignette_detected)? ("true"):("false")) << std::endl;
    std::cout << "=============================================================" << std::endl;
}

