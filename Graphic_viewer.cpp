//
// Created by gionimbus on 1/26/26.
//

#include "Graphic_viewer.h"

Graphic_viewer::Graphic_viewer() {
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "", sf::Style::Close | sf::Style::Titlebar);
}

double Graphic_viewer::transform_to_window_coordinates_x(double x) const {
    return x + WINDOW_WIDTH / 2.;
}

double Graphic_viewer::transform_to_window_coordinates_y(double y) const {
    return y + WINDOW_HEIGHT / 2.;
}

