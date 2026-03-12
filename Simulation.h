//
// Created by gionimbus on 1/7/26.
//

#ifndef ASTERISM_VALIDATOR_SIMULATION_H
#define ASTERISM_VALIDATOR_SIMULATION_H

#include "helper.h"
#include "transformations.h"
#include "Asterism.h"
#include "Board_set.h"
#include "A_star.h"

enum class Movement {linear, outside_technical_field, safe_basic, A_star, none};

class Simulation {
public:
    Simulation();
    bool is_start_valid () const;
    bool is_destination_valid () const;
    bool is_destination_reached () const;
    bool is_collision_detected () const;
    double get_duration () const;
    void run (Movement movement_type, Board_set& board_set, const Asterism& movement_start, const Asterism& movement_destination = Asterism());
    void print_results() const;

private:
    Movement type;

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

    void reset_fields();

    void run_linear (Board_set& board_set, const Asterism& movement_start, const Asterism& movement_destination);
    void run_safe_basic (Board_set& board_set, const Asterism& movement_start, const Asterism& movement_destination);
    void run_outside_tech_field (Board_set& board_set, const Asterism& movement_start);
    void run_A_star (Board_set& board_set, const Asterism& movement_start, const Asterism& movement_destination);
    void run_A_star_segment (Board_set& board_set, const Asterism& segment_start, const Asterism& segment_destination);
};


#endif //ASTERISM_VALIDATOR_SIMULATION_H