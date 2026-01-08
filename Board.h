//
// Created by gionimbus on 12/16/25.
//

#ifndef ASTERISM_VALIDATOR_BOARD_H
#define ASTERISM_VALIDATOR_BOARD_H

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/draw_polygon_set_2.h>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point;
typedef CGAL::Polygon_2<Kernel> Polygon;
typedef CGAL::Vector_2<Kernel> Vector;
typedef CGAL::Direction_2<Kernel> Direction;
typedef CGAL::Polygon_set_2<Kernel> PolygonSet;

constexpr double BOARD_VELOCITY = 4.; // mm/s
constexpr double RAW_TOLERANCE = 1;
constexpr double FINE_TOLERANCE = 0.1;

enum class Board_type {type1, type2, type3};

class Board {
public:
    Polygon profile;
    Point pom; // center of the pom
    Point pom_home;
    Polygon pom_range;

    explicit Board (const Board_type type);
    bool is_in_range (const Point& point) const;
    bool teleport (double delta_x, double delta_y);
    bool teleport (const Point& pom_destination);
    bool is_reached (const Point& pom_destination) const;
    bool move_step_linear (const Point& pom_destination, const double distance_step);
    void teleport_home ();
};


#endif //ASTERISM_VALIDATOR_BOARD_H