//
// Created by gionimbus on 1/7/26.
//

#ifndef ASTERISM_VALIDATOR_SIMULATION_H
#define ASTERISM_VALIDATOR_SIMULATION_H

#include "Board_set.h"

constexpr int MAX_TIME_INDEX = 10000;
constexpr double SIMULATION_TIME_STEP = 0.1; // seconds
constexpr double SIMULATION_DISTANCE_STEP = BOARD_VELOCITY * SIMULATION_TIME_STEP; // mm

enum class Simulation_type {linear_trajectory, non_linear_trajectory, none};

class Simulation {
public:
    Simulation_type type;
    Asterism start;
    Asterism destination;
    bool destination_reached;
    bool collision_detected;
    bool fov_small_vignette_detected;
    bool fov_large_vignette_detected;
    double duration;

    Simulation ();
    bool linear_trajectory (Board_set& boards, const Asterism& trajectory_start, const Asterism& trajectory_destination);
    void print_results() const;
};


#endif //ASTERISM_VALIDATOR_SIMULATION_H