//
// Created by gionimbus on 12/16/25.
//

#ifndef ASTERISM_VALIDATOR_BOARD_H
#define ASTERISM_VALIDATOR_BOARD_H

// See Computational Geometry Algorithms Library (CGAL)
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/draw_polygon_set_2.h>

// By defining a Simple_cartesian<double> kernel we choose to operate with double precision arithmetics
typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point;
typedef CGAL::Polygon_2<Kernel> Polygon;
typedef CGAL::Vector_2<Kernel> Vector;
typedef CGAL::Direction_2<Kernel> Direction;
typedef CGAL::Polygon_set_2<Kernel> PolygonSet;

// Represents the board velocity (in mm/s) used in Board::move_step_linear
constexpr double BOARD_VELOCITY = 4.;

// Used to parametrize the Board constructor
enum class Board_type {type1, type2, type3};

// Represents the board with its profile (a polygonal approximation), its pick off mirror (pom) center, the home
// position of the pom and the pom range (a rectangular field of 300 * 600 mm)
class Board {
public:
    Polygon profile;
    // Center of the pom
    Point pom;
    Point pom_home;
    Polygon pom_range;

    // The constructor is parametrized to build only 3 possible types of boards
    explicit Board (const Board_type type);

    // Returns TRUE if the point is inside the pom range (or on its boundary), FALSE otherwise
    bool is_in_range (const Point& point) const;

    // Directly moves the profile and the pom by delta_x and delta_y only if the new position of the pom is in its range.
    // Returns TRUE if the teleportation is successful, FALSE otherwise
    bool teleport (double delta_x, double delta_y);

    // Same behavior as the previous method, but takes a Point reference as argument
    bool teleport (const Point& pom_destination);

    // Directly moves the profile and the pom in the initial position
    void teleport_home ();

    // Checks if the current pom position falls in a circular interval centered in pom_destination. The circular
    // interval radius is the constant Simulation::SIMULATION_DISTANCE_STEP
    bool is_destination_reached (const Point& pom_destination) const;

    // Moves the profile and the pom towards the pom_destination in a linear trajectory by a fixed distance_step.
    // Returns TRUE if pom has reached pom_destination, FALSE otherwise
    bool move_step_linear (const Point& pom_destination, const double distance_step);

    // Calculates and returns the Euclidean distance between the current pom position and pom_destination
    double calculate_distance (const Point& pom_destination) const;
};


#endif //ASTERISM_VALIDATOR_BOARD_H