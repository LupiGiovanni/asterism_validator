//
// Created by gionimbus on 12/30/25.
//

#ifndef ASTERISM_VALIDATOR_BOARD_SET_H
#define ASTERISM_VALIDATOR_BOARD_SET_H

#include <vector>
#include "helper.h"
#include "Board.h"
#include "Asterism.h"
#include "coordinates.h"

class Board_set {
public:
    Board_set();
    std::vector<int> get_targets() const;
    const std::vector<Board>& get_boards() const;
    bool detect_collision() const;
    bool detect_vignette_fov_small() const;
    bool detect_vignette_fov_large() const;
    double calculate_distance (const Asterism& destination_asterism) const;
    void assign_targets (const Asterism& destination_asterism);
    void teleport (const Asterism& destination_asterism);
    bool is_destination_reached (const Asterism& destination_asterism, double tolerance) const;
    bool is_destination_reached (const Asterism& destination_asterism) const;
    bool is_aligned_x (const Asterism& destination_asterism) const;
    bool is_aligned_y (const Asterism& destination_asterism) const;
    bool is_in_technical_field () const;
    bool is_in_safe_zone () const;
    bool move (const Asterism& destination_asterism, double distance_step);
    bool move_outside_tech_field (double distance_step);
    bool move_to_safe_zone (double distance_step);
    bool move_along_x (const Asterism& destination_asterism, double distance_step);
    bool move_along_y (const Asterism& destination_asterism, double distance_step);

private:
    std::vector<Board> boards;

    std::vector<int> targets = {};

    Circle technical_field;
    Polygon fov_small;
    Polygon fov_large;
};

#endif //ASTERISM_VALIDATOR_BOARD_SET_H