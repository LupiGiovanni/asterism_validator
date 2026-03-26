//
// Created by gionimbus on 12/30/25.
//

#ifndef ASTERISM_VALIDATOR_BOARD_SET_H
#define ASTERISM_VALIDATOR_BOARD_SET_H

#include <vector>
#include "helper.h"
#include "Board.h"
#include "Asterism.h"
#include "CAD_coordinates.h"

class Board_set {
public:
    Board_set ();

    const std::vector<Board>& get_boards () const;
    std::vector<int> get_targets () const;
    void set_targets (const std::vector<int>& new_targets);

    void assign_targets (const Asterism& destination_asterism);

    bool detect_collision () const;
    bool detect_collision_buffers () const;
    bool detect_vignette_fov_small () const;
    bool detect_vignette_fov_large () const;

    double calculate_distance (const Asterism& destination_asterism) const;

    void teleport (const Asterism& destination_asterism);

    bool move (const Asterism& destination_asterism, double distance_step);
    bool move_outside_tech_field (double distance_step);
    bool move_to_safe_zone (double distance_step);
    bool move_along_x (const Asterism& destination_asterism, double distance_step); // x in board local reference system
    bool move_along_y (const Asterism& destination_asterism, double distance_step); // y in board local reference system

    bool is_destination_in_range (const Asterism& destination_asterism) const;
    bool is_destination_reached (const Asterism& destination_asterism, double tolerance = TOLERANCE) const;
    bool is_destination_aligned_x (const Asterism& destination_asterism) const;
    bool is_destination_aligned_y (const Asterism& destination_asterism) const;
    bool is_in_technical_field () const;
    bool is_in_safe_zone () const;

private:
    std::vector<Board> boards;

    std::vector<int> targets = {};

    Circle technical_field;
    Polygon fov_small;
    Polygon fov_large;
};


#endif //ASTERISM_VALIDATOR_BOARD_SET_H