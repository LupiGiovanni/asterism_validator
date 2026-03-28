//
// Created by gionimbus on 1/26/26.
//

#ifndef ASTERISM_VALIDATOR_GRAPHIC_VIEWER_H
#define ASTERISM_VALIDATOR_GRAPHIC_VIEWER_H

#include <SFML/Graphics.hpp>
#include "Simulation.h"

class Graphic_viewer {
public:
    Graphic_viewer ();

    void draw (const Board_set& board_set);
    void draw (const Board_set& board_set, const Asterism& asterism);
    void draw (const Board_set& board_set, const Asterism& start, const Asterism& destination);
    void draw (const Asterism& start, const Asterism& destination);

    void animate (Movement movement_type, const Asterism& start, const Asterism& destination = Asterism());

private:
    std::vector< sf::VertexArray > boards;
    std::vector< sf::VertexArray > trajectories;
    std::vector< sf::ConvexShape > pom_ranges;
    sf::ConvexShape fov_small;
    sf::ConvexShape fov_large;
    sf::CircleShape technical_field;
    std::vector<sf::CircleShape> start_asterism;
    std::vector<sf::CircleShape> destination_asterism;

    sf::Clock movement_clock;
    sf::Time movement_delay;

    sf::Clock animation_clock;
    sf::Time animation_delay;

    double transform_into_window_x (double x_coordinate) const;
    double transform_into_window_y (double y_coordinate) const;

    void setup_pom_ranges ();
    void setup_fov_large ();
    void setup_fov_small ();
    void setup_technical_field ();
    void setup_boards (const Board_set& board_set);
    void setup_start_asterism (const Asterism& asterism);
    void setup_destination_asterism (const Asterism& asterism);

    void animate_outside_tech_field (const Asterism& start);
    void animate_linear (const Asterism& start, const Asterism& destination);
    void animate_safe_basic (const Asterism& start, const Asterism& destination);
    void animate_A_star (const Asterism& start, const Asterism& destination);

    void clear_trajectories ();
    void update_trajectories (const Board_set& board_set);

    void rotate_clockwise_around_center (sf::ConvexShape& shape, float angle_degrees);
};


#endif //ASTERISM_VALIDATOR_GRAPHIC_VIEWER_H