//
// Created by gionimbus on 12/16/25.
//

#ifndef ASTERISM_VALIDATOR_HELPER_H
#define ASTERISM_VALIDATOR_HELPER_H

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/draw_polygon_set_2.h>
#include <CGAL/Aff_transformation_2.h>
#include <CGAL/approximated_offset_2.h>
#include <sciplot/sciplot.hpp>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point;
typedef CGAL::Polygon_2<Kernel> Polygon;
typedef CGAL::Vector_2<Kernel> Vector;
typedef CGAL::Line_2<Kernel> Line;
typedef CGAL::Direction_2<Kernel> Direction;
typedef CGAL::Polygon_set_2<Kernel> PolygonSet;
typedef CGAL::Circle_2<Kernel> Circle;
typedef CGAL::Aff_transformation_2<Kernel> Transformation;

constexpr int DECIMAL_PLACES_PRINTED = 6;
constexpr int MAX_ITERATION_INDEX = 10000;
// TODO: maybe add public method to set board velocity
constexpr double BOARD_VELOCITY = 10.; // mm/s
constexpr double BOARD_BUFFER_WIDTH = 10.; // mm
constexpr double SIMULATION_TIME_STEP = 0.05; // seconds
constexpr double SIMULATION_DISTANCE_STEP = BOARD_VELOCITY * SIMULATION_TIME_STEP; // mm
constexpr double TECHNICAL_FIELD_RADIUS = 265.2; // mm
constexpr int BOARDS_COUNT = 3;
constexpr int GENERATED_DATASET_SIZE = 1000;
constexpr double TOLERANCE = SIMULATION_DISTANCE_STEP; // mm
constexpr int HISTOGRAM_INTERVALS_COUNT =15; // default = 15
constexpr int HISTOGRAM_FONT_SIZE = 12; // default = 12

inline void rotate (Polygon& polygon, double angle_radians) {
    Transformation rotation (CGAL::ROTATION, std::sin(angle_radians), std::cos(angle_radians));
    for (auto& vertex : polygon)
        vertex = rotation.transform(vertex);
}

inline void rotate (Point& point, double angle_radians) {
    Transformation rotation (CGAL::ROTATION, std::sin(angle_radians), std::cos(angle_radians));
    point = rotation.transform(point);
}

inline Polygon enlarge(const Polygon& polygon, double offset) {
    Polygon p = polygon;
    if (p.is_clockwise_oriented())
        p.reverse_orientation();

    const double eps = 0.1;
    auto offset_poly_with_holes = CGAL::approximated_offset_2(p, offset, eps);

    Polygon enlarged_poly;
    auto outer = offset_poly_with_holes.outer_boundary();

    for (auto c = outer.curves_begin(); c != outer.curves_end(); ++c) {
        auto pt = c->source();
        enlarged_poly.push_back(Point(CGAL::to_double(pt.x()), CGAL::to_double(pt.y())));
    }

    return enlarged_poly;
}


#endif //ASTERISM_VALIDATOR_HELPER_H