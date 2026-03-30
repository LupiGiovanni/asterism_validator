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
constexpr int MAX_ITERATION_INDEX = 10000;
constexpr double BOARD_VELOCITY = 10.; // mm/s
constexpr double SIMULATION_TIME_STEP = 0.05; // seconds
constexpr double SIMULATION_DISTANCE_STEP = BOARD_VELOCITY * SIMULATION_TIME_STEP; // mm
constexpr double TOLERANCE = SIMULATION_DISTANCE_STEP; // mm

// A* search parameters
enum class Heuristic {octile, manhattan};
enum class Fov_options {fov_small_excluded, fov_large_excluded, none};

constexpr std::array<int, 9> DX_octile = {0, 0, 0, 1, -1, 1, 1, -1, -1};
constexpr std::array<int, 9> DY_octile = {0, 1, -1, 0, 0, 1, -1, 1, -1};
constexpr std::array<int, 5> DX_manhattan = {0, 0, 0, 1, -1};
constexpr std::array<int, 5> DY_manhattan = {0, 1, -1, 0, 0};
constexpr int NUM_DIRECTIONS_OCTILE = 9;
constexpr int NUM_DIRECTIONS_MANHATTAN = 5;
constexpr double SEARCH_GRID_SIZE = 30; // mm
constexpr double ORTHOGONAL_COST = 1.;
constexpr double DIAGONAL_COST = 1.41421356237;
constexpr double HEURISTIC_WEIGHT = 1.1;
constexpr double BOARD_BUFFER_WIDTH = 10.; // mm
constexpr double GOAL_REACHED_TOLERANCE = SEARCH_GRID_SIZE * 1.5; // mm
constexpr double EPSILON = std::numeric_limits<double>::epsilon();
constexpr auto HEURISTIC = Heuristic::manhattan;
constexpr auto FOV_OPTIONS = Fov_options::none;

// Graphic rendering parameters
constexpr int WINDOW_HEIGHT = 1000;
constexpr int WINDOW_WIDTH = 1000;
constexpr int BOARD_VERTICES_COUNT = 12;
constexpr int POM_RANGE_VERTICES_COUNT = 4;
constexpr double ASTERISM_CIRCLE_RADIUS = 8.;
constexpr int CONVEX_SHAPES_TRANSPARENCY = 60;
constexpr int MOVEMENT_DELAY = 15; // milliseconds
constexpr int ANIMATION_START_DELAY = 1000; // milliseconds

// Dataset generation parameters
constexpr double TECHNICAL_FIELD_RADIUS = 265.2; // mm
constexpr double GENERATION_AREA_RADIUS = 100; // mm
constexpr int GENERATED_DATASET_SIZE = 100;

// Other parameters
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

inline bool is_equal_double (double a, double b, double epsilon = EPSILON) {
    if (a == b)
        return true;
    double diff = std::abs(a - b);
    return diff < epsilon * std::max(std::abs(a), std::abs(b));
}

#endif //ASTERISM_VALIDATOR_HELPER_H