//
// Created by gionimbus on 12/16/25.
//

#ifndef ASTERISM_VALIDATOR_BOARD_H
#define ASTERISM_VALIDATOR_BOARD_H

#include "helper.h"
#include "coordinates.h"

enum class Board_type {type0, type1, type2};

class Board {
    friend class Board_set;
    friend class Trajectory_generator;
    friend class Search_state;
    friend class Graphic_viewer;
private:
    Polygon profile;
    Point pom;
    Point pom_home;
    Polygon pom_range;

    explicit Board (Board_type type);

    bool is_in_range (const Point& point) const;

    bool teleport (double delta_x, double delta_y);

    bool teleport (const Point& pom_destination);

    void teleport_home ();

    bool is_destination_reached (const Point& pom_destination) const;

    bool is_in_technical_field (const Circle& technical_field) const;

    double calculate_distance (const Point& pom_destination) const;

    bool move (const Point& pom_destination, double distance_step);

    bool move_outside_tech_field (const Circle& tech_field, double distance_step);

public:
    const Polygon& get_profile () const;
};


#endif //ASTERISM_VALIDATOR_BOARD_H