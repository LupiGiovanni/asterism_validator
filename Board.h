//
// Created by gionimbus on 12/16/25.
//

#ifndef ASTERISM_VALIDATOR_BOARD_H
#define ASTERISM_VALIDATOR_BOARD_H

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/draw_polygon_set_2.h>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point;
typedef CGAL::Polygon_2<Kernel> Polygon;
typedef CGAL::Vector_2<Kernel> Vector;
typedef CGAL::Polygon_set_2<Kernel> PolygonSet;

enum class Board_type {type_1, type_2, type_3};

struct Board {
    Polygon profile;

    Point pom_centre;
    Point starting_pom_centre;
    Polygon pom_range;

    explicit Board (const Board_type type);
    bool is_in_range (const Point& point) const;
    bool move (double delta_x, double delta_y);
    bool move_to_ngs (const Point& ngs);
};


#endif //ASTERISM_VALIDATOR_BOARD_H