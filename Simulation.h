//
// Created by gionimbus on 1/7/26.
//

#ifndef ASTERISM_VALIDATOR_SIMULATION_H
#define ASTERISM_VALIDATOR_SIMULATION_H

#include "Board_set.h"

constexpr int MAX_ITERATION_INDEX = 10000;
constexpr double SIMULATION_TIME_STEP = 0.05; // seconds
constexpr double SIMULATION_DISTANCE_STEP = BOARD_VELOCITY * SIMULATION_TIME_STEP; // mm

// Parameterize the trajectory type
enum class Trajectory_type {linear_trajectory, non_linear_trajectory, none};

// The class represents a simulation of the trajectories of the 3 boards from a start position (represented by an
// asterism) to a destination position (also represented by an asterism). The simulation is discrete in time and space
// (see constants above). We move the boards by one SIMULATION_DISTANCE_STEP every SIMULATION_TIME_STEP. At each
// iteration of the simulation we perform a check for boards collisions and for Field of view (FoV) vignetting. The
// simulation is stopped if 1 of the following 3 condition is met:
//     1) a collision is detected
//     2) the destination asterism is reached
//     3) the number of maximum iterations (represented by MAX_ITERATION_INDEX) is exceeded
// The simulated trajectories can be of different types (linear, non-linear, ...)
class Simulation {
public:
    Trajectory_type type;
    Asterism start;
    Asterism destination;
    bool destination_reached;
    bool collision_detected;
    bool fov_small_vignette_detected;
    bool fov_large_vignette_detected;
    double duration;  // seconds
    int iterations;
    bool max_iterations_exceeded;

    Simulation ();

    void reset_result_fields ();

    // This method simulates linear trajectories for the 3 boards from trajectory_start to trajectory_destination.
    // Returns TRUE if the boards reach their destinations and saves in the class fields the results of the simulation.
    // Returns FALSE if a collision is detected or if the maximum number of iterations is exceeded.
    bool run_linear_trajectory (Board_set& boards, const Asterism& trajectory_start, const Asterism& trajectory_destination);

    // Strongly recommended to use after each simulation to better visualize results
    void print_results() const;
};


#endif //ASTERISM_VALIDATOR_SIMULATION_H