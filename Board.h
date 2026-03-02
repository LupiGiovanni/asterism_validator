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
private:
    Polygon profile;
    Point pom;
    Point pom_home;
    Polygon pom_range;
    Polygon pom_safe_zone;

    explicit Board (Board_type type);
    bool is_in_range (const Point& point) const;
    bool teleport (double delta_x, double delta_y);
    bool teleport (const Point& pom_destination);
    void teleport_home ();
    bool is_destination_reached (const Point& pom_destination, double tolerance) const;
    bool is_destination_reached (const Point& pom_destination) const;
    bool is_aligned_x (const Point& pom_destination) const;
    bool is_aligned_y (const Point& pom_destination) const;
    bool is_in_technical_field (const Circle& technical_field) const;
    bool is_in_safe_zone () const;
    double calculate_distance (const Point& pom_destination) const;
    bool move (const Point& pom_destination, double distance_step);
    bool move_outside_tech_field (const Circle& tech_field, double distance_step);
    bool move_along_x (const Point& pom_destination, double distance_step);
    bool move_along_y (const Point& pom_destination, double distance_step);
    bool move_to_safe_zone (double distance_step);
    Point find_aligned_point_x (const Point& pom_destination) const;
    Point find_aligned_point_y (const Point& pom_destination) const;

public:
    const Polygon& get_profile () const;
};


#endif //ASTERISM_VALIDATOR_BOARD_H