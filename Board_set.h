//
// Created by gionimbus on 12/30/25.
//

#ifndef ASTERISM_VALIDATOR_BOARD_SET_H
#define ASTERISM_VALIDATOR_BOARD_SET_H

#include "Board.h"
#include "Asterism.h"

// Used to represent which board moves towards which ngs of an asterism.
// For example, given an Asterism A,  Board_set_targets::ngs_231 means that
//      board1 moves towards A.ngs2
//      board2 moves towards A.ngs3
//      board3 moves towards A.ngs1
enum class Board_set_targets {none, ngs_123, ngs_132, ngs_213, ngs_231, ngs_312, ngs_321};

// Represents a set of 3 boards along with their assigned targets (ngs) and the small and large fields of view (fov)
class Board_set {
public:
    Board board1;
    Board board2;
    Board board3;

    Board_set_targets targets;

    Circle technical_field;
    Polygon fov_small;
    Polygon fov_large;

    // Initializes 3 boards, each one of different type (Board_type::type1, Board_type::type2 and Board_type::type3)
    Board_set();

    // If a collision between boards in current positions is detected, returns TRUE. FALSE otherwise
    bool detect_collision() const;

    // If a vignette of the fov_small by any of the boards in current positions is detected, returns TRUE. Returns
    // FALSE otherwise
    bool detect_vignette_fov_small() const;

    // If a vignette of the fov_large by any of the boards in current positions is detected, returns TRUE. Returns
    // FALSE otherwise
    bool detect_vignette_fov_large() const;

    // This method establishes which boards move towards which ngs of destination_asterism and correspondently sets the
    // 'targets' field
    void assign_targets (const Asterism& destination_asterism);

    // Directly moves the 3 boards to their respective target ngs.
    // Call assign_targets before using this method
    void teleport (const Asterism& destination_asterism);

    // If all the 3 boards have reached their respective target ngs, returns TRUE. FALSE otherwise.
    // Returns FALSE if targets == Board_set_targets::none.
    // See Board::is_destination_reached for more details about how to determine if a single board has reached its
    // target ngs.
    // Call assign_targets before using this method
    bool is_destination_reached (const Asterism& destination_asterism) const;

    // If any portion of any board profile is inside (or on the border of) the technical_field, returns TRUE. Returns
    // FALSE otherwise
    bool is_in_technical_field () const;

    // Moves the 3 boards towards their respective target ngs by a fixed distance_step. If a collision is detected
    // after the movement, TRUE is returned. FALSE is returned otherwise.
    // If targets == Board_set_targets::none, no movement is performed and FALSE is returned.
    // Call assign_targets before using this method
    bool move_step_linear_trajectory (const Asterism& destination_asterism, const double distance_step);

    // Moves the boards away from the technical_field by a fixed distance_step. If a board exits the technical_field,
    // then it's not moved any further
    void move_step_out_of_technical_field (double distance_step);

    // Calculates and returns the distance of the board set from destination_asterism, defined as
    //      distance = d1 + d2 + d3
    // where
    //      d1 = distance between board1.pom and its target ngs
    //      d2 = distance between board2.pom and its target ngs
    //      d3 = distance between board3.pom and its target ngs
    // Call assign_targets before using this method
    double calculate_distance (const Asterism& destination_asterism) const;

    // Draws the current positions of the 3 boards along with their pom ranges and the triangle formed by the 3 ngs of
    // the given asterism.
    // Note that CGAL documentation reports that CGAL::draw functions are subject to segmentation fault errors
    void draw (const Asterism& asterism) const;

    // Draws the current positions of the 3 boards along with their pom ranges.
    // Note that CGAL documentation reports that CGAL::draw functions are subject to segmentation fault errors
    void draw () const;
};

#endif //ASTERISM_VALIDATOR_BOARD_SET_H