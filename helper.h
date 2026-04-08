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
typedef CGAL::Polygon_set_2<Kernel> Polygon_set;
typedef CGAL::Circle_2<Kernel> Circle;
typedef CGAL::Aff_transformation_2<Kernel> Transformation;

// Simulation parameters
constexpr int BOARDS_COUNT = 3;
constexpr int BOARD_VERTICES_COUNT = 12;
constexpr int POM_RANGE_VERTICES_COUNT = 4;
constexpr double TECHNICAL_FIELD_RADIUS = 265.2; // mm
constexpr int MAX_ITERATION_INDEX = 10000;
constexpr double BOARDS_CRUISE_VELOCITY = 10.; // mm/s
constexpr double SIMULATION_TIME_STEP = 0.05; // seconds
constexpr double DESTINATION_REACHED_TOLERANCE = BOARDS_CRUISE_VELOCITY * SIMULATION_TIME_STEP; // mm

// A* search parameters
enum class Grid_type {isometric, manhattan};
enum class Fov_options {fov_small_excluded, fov_large_excluded, none};

constexpr auto GRID_TYPE = Grid_type::isometric;
constexpr auto FOV_OPTIONS = Fov_options::none;
constexpr double GRID_SIZE = 30; // mm
constexpr double HEURISTIC_WEIGHT = 1.3;
constexpr double BOARD_BUFFER_WIDTH = 10.; // mm
constexpr double GOAL_REACHED_TOLERANCE = GRID_SIZE * 1.5; // mm
constexpr double SIN45 = 0.70710678118;
constexpr double SIN60 = 0.86602540378;
constexpr double COS60 = 0.5;
constexpr std::array<double, 9> DX_isometric = {0., 0., 0., 1., -1., SIN45, SIN45, -SIN45, -SIN45};
constexpr std::array<double, 9> DY_isometric = {0., 1., -1., 0., 0., SIN45, -SIN45, SIN45, -SIN45};
constexpr std::array<double, 5> DX_manhattan = {0., 0., 0., 1., -1.};
constexpr std::array<double, 5> DY_manhattan = {0., 1., -1., 0., 0.};
constexpr std::array<double, 7> DX_triangular = {0., 1., -1., COS60, COS60, -COS60, -COS60};
constexpr std::array<double, 7> DY_triangular = {0., 0, 0., SIN60, -SIN60, SIN60, -SIN60};
constexpr int NUM_DIRECTIONS_ISOMETRIC = 9;
constexpr int NUM_DIRECTIONS_MANHATTAN = 5;
constexpr int NUM_DIRECTIONS_TRIANGULAR = 7;

// Graphic rendering parameters
constexpr int WINDOW_HEIGHT = 1000;
constexpr int WINDOW_WIDTH = 1000;
constexpr double ASTERISM_CIRCLE_RADIUS = 8.;
constexpr int CONVEX_SHAPES_TRANSPARENCY = 60;
constexpr int MOVEMENT_DELAY = 15; // milliseconds
constexpr int ANIMATION_START_DELAY = 1000; // milliseconds

// Dataset generation parameters
constexpr double GENERATION_AREA_RADIUS = 100; // mm
constexpr int GENERATED_DATASET_SIZE = 100;

// Other parameters
constexpr double EPSILON = std::numeric_limits<double>::epsilon();
constexpr int DECIMAL_PLACES_PRINTED = 6;
constexpr int HISTOGRAM_INTERVALS_COUNT = 15; // default = 15
constexpr int HISTOGRAM_FONT_SIZE = 12; // default = 12

// Helper functions
inline void rotate (Polygon& polygon, double angle_radians) {
    Transformation rotation (CGAL::ROTATION, std::sin(angle_radians), std::cos(angle_radians));
    for (auto& vertex : polygon)
        vertex = rotation.transform(vertex);
}

inline void rotate (Point& point, double angle_radians) {
    Transformation rotation (CGAL::ROTATION, std::sin(angle_radians), std::cos(angle_radians));
    point = rotation.transform(point);
}

inline Polygon enlarge (const Polygon& polygon, double offset) {
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

inline bool is_equal_double (double a, double b, double epsilon = std::numeric_limits<double>::epsilon()) {
    if (a == b)
        return true;
    double diff = std::abs(a - b);
    return diff < epsilon || diff < epsilon * std::max(std::abs(a), std::abs(b));
}

inline bool is_greater_double (double a, double b, double epsilon = std::numeric_limits<double>::epsilon()) {
    double diff = a - b;
    return diff > epsilon && diff > epsilon * std::max(std::abs(a), std::abs(b));
}

#endif //ASTERISM_VALIDATOR_HELPER_H