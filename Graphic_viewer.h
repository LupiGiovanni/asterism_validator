//
// Created by gionimbus on 1/26/26.
//

#ifndef ASTERISM_VALIDATOR_GRAPHIC_VIEWER_H
#define ASTERISM_VALIDATOR_GRAPHIC_VIEWER_H

#include <SFML/Graphics.hpp>
#include "helper.h"
#include "Board_set.h"
#include "Asterism.h"

constexpr int WINDOW_HEIGHT = 1000;
constexpr int WINDOW_WIDTH = 1000;

constexpr int BOARD_VERTICES_COUNT = 12;
constexpr int POM_RANGE_VERTICES_COUNT = 4;

class Graphic_viewer {
public:
    Graphic_viewer();

    void draw(const Board_set& board_set);
    void draw(const Board_set& board_set, const Asterism& asterism);
    void draw(const Board_set& board_set, const Asterism& start_asterism, const Asterism& destination_asterism);

private:
    sf::RenderWindow window;
    std::vector<sf::VertexArray> boards;
    std::vector<sf::ConvexShape> pom_ranges;
    sf::ConvexShape fov_small;
    sf::ConvexShape fov_large;
    sf::CircleShape technical_field;
    sf::VertexArray start_asterism;
    sf::VertexArray destination_asterism;

    double window_coordinate_x (double x) const;
    double window_coordinate_y (double y) const;

    void setup_pom_ranges();
    void setup_fov_large();
    void setup_fov_small();
    void setup_technical_field();
    void rotate_clockwise_around_center(sf::ConvexShape& shape, float angle_degrees);
    void rotate_clockwise_around_center(sf::VertexArray& shape, float angle_degrees);

    // void draw_boards();
    // void draw_pom_ranges();
    // void draw_tech_field();
    // void draw_fov_small();
    // void draw_fov_large();
    // void draw_start_asterism();
    // void draw_destination_asterism();
    // void draw_trajectories();
};


#endif //ASTERISM_VALIDATOR_GRAPHIC_VIEWER_H