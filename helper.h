//
// Created by gionimbus on 12/16/25.
//

#ifndef ASTERISM_VALIDATOR_HELPER_H
#define ASTERISM_VALIDATOR_HELPER_H

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/draw_polygon_set_2.h>
#include <CGAL/Aff_transformation_2.h>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point;
typedef CGAL::Polygon_2<Kernel> Polygon;
typedef CGAL::Vector_2<Kernel> Vector;
typedef CGAL::Direction_2<Kernel> Direction;
typedef CGAL::Polygon_set_2<Kernel> PolygonSet;
typedef CGAL::Circle_2<Kernel> Circle;
typedef CGAL::Aff_transformation_2<Kernel> Transformation;

constexpr int DECIMAL_PLACES_PRINTED = 6;
constexpr int MAX_ITERATION_INDEX = 10000;
constexpr double BOARD_VELOCITY = 10.; // mm/s
constexpr double SIMULATION_TIME_STEP = 0.05; // seconds
constexpr double SIMULATION_DISTANCE_STEP = BOARD_VELOCITY * SIMULATION_TIME_STEP; // mm
constexpr double TECHNICAL_FIELD_RADIUS = 265.2; // mm
constexpr int BOARDS_COUNT = 3;
constexpr int GENERATED_DATASET_SIZE = 1000;
constexpr double TOLERANCE = SIMULATION_DISTANCE_STEP;

inline void rotate (Polygon& polygon, double angle_radians) {
    Transformation rotation (CGAL::ROTATION, std::sin(angle_radians), std::cos(angle_radians));
    for (auto& vertex : polygon)
        vertex = rotation.transform(vertex);
}

inline void rotate (Point& point, double angle_radians) {
    Transformation rotation (CGAL::ROTATION, std::sin(angle_radians), std::cos(angle_radians));
    point = rotation.transform(point);
}

#endif //ASTERISM_VALIDATOR_HELPER_H