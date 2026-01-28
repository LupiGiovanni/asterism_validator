//
// Created by gionimbus on 1/26/26.
//

#ifndef ASTERISM_VALIDATOR_GRAPHIC_VIEWER_H
#define ASTERISM_VALIDATOR_GRAPHIC_VIEWER_H

#include <SFML/Graphics.hpp>
#include "helper.h"
#include "Board_set.h"
#include "Asterism.h"
#include "Simulation.h"

constexpr int WINDOW_HEIGHT = 1000;
constexpr int WINDOW_WIDTH = 1000;

constexpr int BOARD_VERTICES_COUNT = 12;
constexpr int POM_RANGE_VERTICES_COUNT = 4;
constexpr double ASTERISM_CIRCLE_RADIUS = 8.;
constexpr int CONVEX_SHAPES_TRANSPARENCY = 60;
constexpr int MOVEMENT_DELAY = 15; // milliseconds
constexpr int ANIMATION_START_DELAY = 1000; // milliseconds

class Graphic_viewer {
public:
    Graphic_viewer();

    void draw(const Board_set& board_set);
    void draw(const Board_set& board_set, const Asterism& asterism);
    void draw(const Board_set& board_set, const Asterism& start, const Asterism& destination);

    void animate(Movement movement_type, const Asterism& start, const Asterism& destination = Asterism());

private:
    std::vector<sf::VertexArray> boards;
    std::vector<sf::ConvexShape> pom_ranges;
    sf::ConvexShape fov_small;
    sf::ConvexShape fov_large;
    sf::CircleShape technical_field;
    std::vector<sf::CircleShape> start_asterism;
    std::vector<sf::CircleShape> destination_asterism;

    sf::Clock movement_clock;
    sf::Time movement_delay;

    sf::Clock animation_start_clock;
    sf::Time animation_start_delay;

    double window_coordinate_x (double x) const;
    double window_coordinate_y (double y) const;

    void setup_pom_ranges();
    void setup_fov_large();
    void setup_fov_small();
    void setup_technical_field();
    void setup_boards(const Board_set& board_set);
    void setup_start_asterism(const Asterism& asterism);
    void setup_destination_asterism(const Asterism& asterism);
    void rotate_clockwise_around_center(sf::ConvexShape& shape, float angle_degrees);
    void animate_outside_tech_field(const Asterism& start);
    void animate_linear_trajectory(const Asterism& start, const Asterism& destination);
};


#endif //ASTERISM_VALIDATOR_GRAPHIC_VIEWER_H