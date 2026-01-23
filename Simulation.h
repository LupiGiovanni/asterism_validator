//
// Created by gionimbus on 1/7/26.
//

#ifndef ASTERISM_VALIDATOR_SIMULATION_H
#define ASTERISM_VALIDATOR_SIMULATION_H

#include "Board_set.h"

constexpr int MAX_ITERATION_INDEX = 10000;
constexpr double SIMULATION_TIME_STEP = 0.05; // seconds
constexpr double SIMULATION_DISTANCE_STEP = BOARD_VELOCITY * SIMULATION_TIME_STEP; // mm

// Parameterize the movement type
enum class Movement_type {linear_trajectory, non_linear_trajectory, out_of_technical_field, none};

// The class represents a simulation of the trajectories of the 3 boards from a start position (represented by an
// asterism) to a destination position (also represented by an asterism). The simulation is discrete in time and space
// (see constants above). We move the boards by one SIMULATION_DISTANCE_STEP every SIMULATION_TIME_STEP. At each
// iteration of the simulation we perform a check for boards collisions and for field of view (fov) vignetting. The
// simulation is stopped if one of the following 3 conditions is met:
//     1) a collision is detected
//     2) the destination asterism is reached
//     3) the number of maximum iterations (represented by MAX_ITERATION_INDEX) is exceeded
// The simulated trajectories can be of different types (linear, non-linear, ...)
class Simulation {
public:
    Simulation();

    bool is_destination_reached () const;
    double get_duration () const;
    bool is_start_valid () const;
    bool is_destination_valid () const;
    bool is_collision_detected () const;

    // This method simulates linear trajectories for the 3 boards from trajectory_start to trajectory_destination.
    // Returns TRUE if the boards reach their destinations and saves in the class fields the results of the simulation.
    // Returns FALSE if a collision is detected or if the maximum number of iterations is exceeded
    bool run_linear_trajectory (Board_set& boards, const Asterism& trajectory_start, const Asterism& trajectory_destination);

    // This method simulates the movement of the 3 boards out of the technical field, starting from movement_start and
    // going in linear trajectories.
    // Returns TRUE if the boards exit the technical field and saves in the class fields the results of the simulation.
    // Returns FALSE if a collision is detected or if the maximum number of iterations is exceeded.
    // Note that with this type of movement the 'destination' asterism is not relevant and has all coordinates set to
    // zero
    bool run_out_of_technical_field (Board_set& boards, const Asterism& movement_start);

    // Strongly recommended to use after each simulation to better visualize results
    void print_results() const;

private:
    Movement_type type;

    Asterism start;
    bool start_valid;

    Asterism destination;
    bool destination_valid;
    bool destination_reached;
    double distance_from_destination;

    bool collision_detected;
    bool fov_small_vignette_detected;
    bool fov_large_vignette_detected;

    double duration;  // seconds
    int iterations;
    bool max_iterations_exceeded;

    void reset_result_fields();
};


#endif //ASTERISM_VALIDATOR_SIMULATION_H