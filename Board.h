//
// Created by gionimbus on 12/16/25.
//

#ifndef ASTERISM_VALIDATOR_BOARD_H
#define ASTERISM_VALIDATOR_BOARD_H

#include "helper.h"

enum class Board_type {type0, type1, type2};

class Board {
    friend class Board_set;

public:
    const Polygon& get_profile () const;
    const Point& get_pom_position () const;
    double get_velocity () const;

    void set_velocity (double new_velocity);

private:
    Polygon profile;
    Polygon profile_buffer;
    Point pom;
    Point pom_home;
    Polygon pom_range;
    Polygon pom_safe_zone;
    double velocity;

    explicit Board (Board_type type);

    bool teleport (double delta_x, double delta_y);
    bool teleport (const Point& pom_destination);
    void teleport_home ();

    bool step_move (const Point& pom_destination);
    bool step_move_outside_tech_field (const Circle& tech_field);
    bool step_move_to_safe_zone ();
    bool step_move_along_x (const Point& pom_destination); // x in board local reference system
    bool step_move_along_y (const Point& pom_destination); // y in board local reference system

    bool is_in_range (const Point& point) const;
    bool is_destination_reached (const Point& pom_destination, double tolerance = DESTINATION_REACHED_TOLERANCE) const;
    bool is_in_technical_field (const Circle& technical_field) const;
    bool is_in_safe_zone () const;
    bool is_destination_aligned_x (const Point& pom_destination) const; // x in board local reference system
    bool is_destination_aligned_y (const Point& pom_destination) const; // y in board local reference system

    double calculate_distance (const Point& pom_destination) const;
    Point find_aligned_point_x (const Point& pom_destination) const; // x in board local reference system
    Point find_aligned_point_y (const Point& pom_destination) const; // y in board local reference system
};


#endif //ASTERISM_VALIDATOR_BOARD_H