//
// Created by gionimbus on 1/26/26.
//

#include "Graphic_viewer.h"

Graphic_viewer::Graphic_viewer() {
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "", sf::Style::Close | sf::Style::Titlebar);

    for (int j = 0; j < BOARDS_COUNT; j++) {
        boards.push_back( sf::VertexArray(sf::LineStrip, BOARD_VERTICES_COUNT + 1) );
        pom_ranges.push_back(sf::ConvexShape(4));
    }

    setup_pom_ranges();
    setup_fov_large();
    setup_fov_small();
    setup_technical_field();

    for (auto& shape : pom_ranges)
        rotate_clockwise_around_center(shape, -90.f);
}

double Graphic_viewer::window_coordinate_x(double x) const {
    return x + WINDOW_WIDTH / 2.;
}

double Graphic_viewer::window_coordinate_y(double y) const {
    return y + WINDOW_HEIGHT / 2.;
}

void Graphic_viewer::setup_pom_ranges() {
    pom_ranges[0].setPoint(0, sf::Vector2f(window_coordinate_x(coordinates::N1.x()), window_coordinate_y(coordinates::N1.y())));
    pom_ranges[0].setPoint(1, sf::Vector2f(window_coordinate_x(coordinates::O1.x()), window_coordinate_y(coordinates::O1.y())));
    pom_ranges[0].setPoint(2, sf::Vector2f(window_coordinate_x(coordinates::P1.x()), window_coordinate_y(coordinates::P1.y())));
    pom_ranges[0].setPoint(3, sf::Vector2f(window_coordinate_x(coordinates::Q1.x()), window_coordinate_y(coordinates::Q1.y())));

    pom_ranges[1].setPoint(0, sf::Vector2f(window_coordinate_x(coordinates::N2.x()), window_coordinate_y(coordinates::N2.y())));
    pom_ranges[1].setPoint(1, sf::Vector2f(window_coordinate_x(coordinates::O2.x()), window_coordinate_y(coordinates::O2.y())));
    pom_ranges[1].setPoint(2, sf::Vector2f(window_coordinate_x(coordinates::P2.x()), window_coordinate_y(coordinates::P2.y())));
    pom_ranges[1].setPoint(3, sf::Vector2f(window_coordinate_x(coordinates::Q2.x()), window_coordinate_y(coordinates::Q2.y())));

    pom_ranges[2].setPoint(0, sf::Vector2f(window_coordinate_x(coordinates::N3.x()), window_coordinate_y(coordinates::N3.y())));
    pom_ranges[2].setPoint(1, sf::Vector2f(window_coordinate_x(coordinates::O3.x()), window_coordinate_y(coordinates::O3.y())));
    pom_ranges[2].setPoint(2, sf::Vector2f(window_coordinate_x(coordinates::P3.x()), window_coordinate_y(coordinates::P3.y())));
    pom_ranges[2].setPoint(3, sf::Vector2f(window_coordinate_x(coordinates::Q3.x()), window_coordinate_y(coordinates::Q3.y())));
}

void Graphic_viewer::setup_fov_large() {
    fov_large.setPointCount(4);
    fov_large.setPoint(0, sf::Vector2f(window_coordinate_x(coordinates::R.x()), window_coordinate_y(coordinates::R.y())));
    fov_large.setPoint(1, sf::Vector2f(window_coordinate_x(coordinates::S.x()), window_coordinate_y(coordinates::S.y())));
    fov_large.setPoint(2, sf::Vector2f(window_coordinate_x(coordinates::T.x()), window_coordinate_y(coordinates::T.y())));
    fov_large.setPoint(3, sf::Vector2f(window_coordinate_x(coordinates::U.x()), window_coordinate_y(coordinates::U.y())));
}

void Graphic_viewer::setup_fov_small() {
    fov_small.setPointCount(4);
    fov_small.setPoint(0, sf::Vector2f(window_coordinate_x(coordinates::V.x()), window_coordinate_y(coordinates::V.y())));
    fov_small.setPoint(1, sf::Vector2f(window_coordinate_x(coordinates::W.x()), window_coordinate_y(coordinates::W.y())));
    fov_small.setPoint(2, sf::Vector2f(window_coordinate_x(coordinates::X.x()), window_coordinate_y(coordinates::X.y())));
    fov_small.setPoint(3, sf::Vector2f(window_coordinate_x(coordinates::Y.x()), window_coordinate_y(coordinates::Y.y())));
}

void Graphic_viewer::setup_technical_field() {
    technical_field.setPointCount(100);
    technical_field.setRadius(TECHNICAL_FIELD_RADIUS);
    technical_field.setOrigin(TECHNICAL_FIELD_RADIUS, TECHNICAL_FIELD_RADIUS);
    technical_field.setPosition(window_coordinate_x(0.), window_coordinate_y(0.));
}

void Graphic_viewer::rotate_clockwise_around_center(sf::ConvexShape& shape, float angle_degrees) {
    sf::Vector2f rotation_center(window_coordinate_x(0.), window_coordinate_y(0.));

    sf::Transform t;
    t.rotate(angle_degrees, rotation_center);

    sf::Vector2f new_position = t.transformPoint(shape.getPosition());

    shape.setPosition(new_position);
    shape.rotate(angle_degrees);
}

void Graphic_viewer::rotate_clockwise_around_center(sf::VertexArray& shape, float angle_degrees) {
    sf::Vector2f rotation_center(window_coordinate_x(0.), window_coordinate_y(0.));

    sf::Transform t;
    t.rotate(angle_degrees, rotation_center);

    for (int i = 0; i < shape.getVertexCount(); i++) {
        sf::Vector2f new_position = t.transformPoint(shape[i].position);
        shape[i].position = new_position;
    }
}



