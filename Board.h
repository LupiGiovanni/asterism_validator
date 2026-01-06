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

enum class Board_type {type_1, type_2, type_3};

struct Board {
    Polygon profile;
    Point pom; // center of the pom
    Point pom_home;
    Polygon pom_range;

    const double velocity = 4.; // mm/s

    explicit Board (const Board_type type);
    bool is_in_range (const Point& point) const;
    bool teleport (double delta_x, double delta_y);
    bool teleport (const Point& pom_destination);
    void move_step_linear (const Point& pom_destination, const double step_mm);
};


#endif //ASTERISM_VALIDATOR_BOARD_H