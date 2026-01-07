//
// Created by gionimbus on 12/30/25.
//

#ifndef ASTERISM_VALIDATOR_BOARD_SET_H

#define ASTERISM_VALIDATOR_BOARD_SET_H

#include "global_functions.h"
#include "Board.h"
#include "Asterism.h"

enum class Board_assignment {none, ngs_123, ngs_132, ngs_213, ngs_231, ngs_312, ngs_321};

class Board_set {
public:
    Board board1;
    Board board2;
    Board board3;

    Board_assignment assignment;

    Polygon fov_small;
    Polygon fov_large;

    Board_set();

    bool detect_collision() const;
    bool detect_vignette_fov_small() const;
    bool detect_vignette_fov_large() const;

    bool are_in_range (const Point& point1, const Point& point2, const Point& point3) const;
    void assign_ngs (const Asterism& asterism);
    bool teleport (const Point& pom1_destination, const Point& pom2_destination, const Point& pom3_destination);
    bool teleport (const Asterism& asterism);
    bool move_step_linear (const Point& pom1_destination, const Point& pom2_destination, const Point& pom3_destination, const double step_mm);
    bool move_step_linear (const Asterism& asterism, const double step_mm);

    void draw (const Asterism& asterism) const;
};


#endif //ASTERISM_VALIDATOR_BOARD_SET_H