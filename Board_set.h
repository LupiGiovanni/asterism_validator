//
// Created by gionimbus on 12/30/25.
//

#ifndef ASTERISM_VALIDATOR_BOARD_SET_H
#define ASTERISM_VALIDATOR_BOARD_SET_H

#include "global_functions.h"
#include "Board.h"
#include "Asterism.h"

// This class represents the 3 boards completed with the small and large field of view (fov).
// A Board_set object also has a current_asterism (the asterism towards which the movements of the boards occur).
// We also store a vector of valid_permutations of the current_asterism.
// Given an Asterism A, a permutation P of A is still an Asterism object with the same natural guide stars as A,
// but listed in a different order.
// For example, if
//
//      A == { ngs1 == a,
//             ngs2 == b,
//             ngs3 == c }
//
// then one of its permutations P is
//
//      P == { ngs1 == b,
//             ngs2 == c,
//             ngs3 == a }
//
// Given a permutation (or equivalently an Asterism) P, board1 always moves towards P.ngs1, board2 towards P.ngs2 and
// board3 towards P.ngs3.
// A permutation P is valid if the 3 boards can be placed in correspondence of their target ngs (i.e. the ngs falls
// within the pom range of the respective board) and if no collision occur in these positions.
class Board_set {
public:
    Board board1;
    Board board2;
    Board board3;

    Asterism current_asterism;
    std::vector<Asterism> valid_permutations;

    Polygon fov_small;
    Polygon fov_large;

    // The constructor initializes 3 boards, each one of different type (Board_type::type1, Board_type::type2 and
    // Board_type::type3). Current_asterism is initialized with all ngs coordinates set to zero. Valid_permutations is
    // initialized as an empty vector. The fov_small and fov_large polygons are also initialized here.
    Board_set();

    // If a collision between boards in current positions is detected, returns TRUE. FALSE otherwise
    bool detect_collision() const;

    // If a vignette of the fov_small by any of the boards in current positions is detected, returns TRUE. Returns
    // FALSE otherwise
    bool detect_vignette_fov_small() const;

    // If a vignette of the fov_large by any of the boards in current positions is detected, returns TRUE. Returns
    // FALSE otherwise
    bool detect_vignette_fov_large() const;

    // Sets the asterism towards which the boards will move.
    // Must be called before calculate_valid_permutations
    void set_current_asterism (const Asterism& asterism);

    // Calculates all possible permutations (3! = 6) of the given asterism
    std::vector<Asterism> calculate_all_permutations (const Asterism& asterism);

    // Calculates and stores in valid_permutations all valid permutations of current_asterism.
    // Given a permutation
    //      P == { ngs1, ngs2, ngs3 }
    // P is valid if
    //      board1 can be placed in correspondence of P.ngs1,
    //      board2 can be placed in correspondence of P.ngs2,
    //      board3 can be placed in correspondence of P.ngs3,
    //      no collisions are detected between the 3 boards in these positions.
    // This method must be called after set_current_asterism
    void calculate_valid_permutations ();

    // Returns TRUE if the given asterism is in valid_permutations, FALSE otherwise
    bool is_valid_permutation (const Asterism& asterism) const;

    // If destination_asterism is a valid permutation. Directly moves the 3 boards to their respective target ngs, i.e.
    //      board1 to destination_asterism.ngs1,
    //      board2 to destination_asterism.ngs2,
    //      board3 to destination_asterism.ngs3,
    // then returns TRUE.
    // If destination_asterism is not a valid permutation, no movement is performed and FALSE is returned
    bool teleport (const Asterism& destination_asterism);

    // If the 3 boards have reached their respective target ngs, returns TRUE. FALSE otherwise.
    // FALSE is also returned if destination_asterism is not a valid permutation.
    // See Board::is_destination_reached for more details about how to determine if a single board has reached its
    // target ngs
    bool is_destination_reached (const Asterism& destination_asterism) const;

    // Moves the 3 boards towards their respective target ngs by a fixed distance_step. If a collision is detected
    // after the movement, TRUE is returned. FALSE is returned otherwise.
    // If destination_asterism is not a valid permutation, no movement is performed and FALSE is returned
    bool move_step_linear (const Asterism& destination_asterism, const double distance_step);

    // Draws the current positions of the 3 boards along with their pom ranges and the triangle formed by the 3 ngs of
    // the given asterism.
    // Note CGAL documentation reports that CGAL::draw functions are subject to segmentation fault errors
    void draw (const Asterism& asterism) const;

    // Draws the current positions of the 3 boards along with their pom ranges.
    // Note CGAL documentation reports that CGAL::draw functions are subject to segmentation fault errors
    void draw () const;
};

#endif //ASTERISM_VALIDATOR_BOARD_SET_H