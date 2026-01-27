//
// Created by gionimbus on 1/26/26.
//

#include "Graphic_viewer.h"

Graphic_viewer::Graphic_viewer() {
    for (int j = 0; j < BOARDS_COUNT; j++) {
        boards.push_back( sf::VertexArray(sf::LineStrip, BOARD_VERTICES_COUNT + 1) );
        pom_ranges.push_back(sf::ConvexShape(POM_RANGE_VERTICES_COUNT));
        start_asterism.push_back(sf::CircleShape(ASTERISM_CIRCLE_RADIUS));
        destination_asterism.push_back(sf::CircleShape(ASTERISM_CIRCLE_RADIUS));
    }

    setup_pom_ranges();
    setup_fov_large();
    setup_fov_small();
    setup_technical_field();
}

double Graphic_viewer::window_coordinate_x(double x) const {
    return x + WINDOW_WIDTH / 2.;
}

double Graphic_viewer::window_coordinate_y(double y) const {
    return -y + WINDOW_HEIGHT / 2.;
}

void Graphic_viewer::setup_pom_ranges() {
    pom_ranges[0].setPoint(0, sf::Vector2f(window_coordinate_x(coordinates::N1.x()), window_coordinate_y(coordinates::N1.y())));
    pom_ranges[0].setPoint(1, sf::Vector2f(window_coordinate_x(coordinates::O1.x()), window_coordinate_y(coordinates::O1.y())));
    pom_ranges[0].setPoint(2, sf::Vector2f(window_coordinate_x(coordinates::P1.x()), window_coordinate_y(coordinates::P1.y())));
    pom_ranges[0].setPoint(3, sf::Vector2f(window_coordinate_x(coordinates::Q1.x()), window_coordinate_y(coordinates::Q1.y())));
    pom_ranges[0].setOutlineThickness(0.);
    pom_ranges[0].setFillColor(sf::Color(255, 0, 0, 50));

    pom_ranges[1].setPoint(0, sf::Vector2f(window_coordinate_x(coordinates::N2.x()), window_coordinate_y(coordinates::N2.y())));
    pom_ranges[1].setPoint(1, sf::Vector2f(window_coordinate_x(coordinates::O2.x()), window_coordinate_y(coordinates::O2.y())));
    pom_ranges[1].setPoint(2, sf::Vector2f(window_coordinate_x(coordinates::P2.x()), window_coordinate_y(coordinates::P2.y())));
    pom_ranges[1].setPoint(3, sf::Vector2f(window_coordinate_x(coordinates::Q2.x()), window_coordinate_y(coordinates::Q2.y())));
    pom_ranges[1].setOutlineThickness(0.);
    pom_ranges[1].setFillColor(sf::Color(0, 255, 0, 50));

    pom_ranges[2].setPoint(0, sf::Vector2f(window_coordinate_x(coordinates::N3.x()), window_coordinate_y(coordinates::N3.y())));
    pom_ranges[2].setPoint(1, sf::Vector2f(window_coordinate_x(coordinates::O3.x()), window_coordinate_y(coordinates::O3.y())));
    pom_ranges[2].setPoint(2, sf::Vector2f(window_coordinate_x(coordinates::P3.x()), window_coordinate_y(coordinates::P3.y())));
    pom_ranges[2].setPoint(3, sf::Vector2f(window_coordinate_x(coordinates::Q3.x()), window_coordinate_y(coordinates::Q3.y())));
    pom_ranges[2].setOutlineThickness(0.);
    pom_ranges[2].setFillColor(sf::Color(0, 0, 255, 50));

    for (auto& it : pom_ranges)
        rotate_clockwise_around_center(it, -90.f);
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
    technical_field.setOutlineThickness(0.);
    technical_field.setFillColor(sf::Color(255, 255, 255, 50));
}

void Graphic_viewer::setup_boards(const Board_set& board_set) {
    std::vector<Board> boards_vector = board_set.get_boards();

    for (int j = 0; j < BOARDS_COUNT; j++) {

        const Polygon& board_profile = boards_vector[j].get_profile();

        for (int i = 0; i < BOARD_VERTICES_COUNT; i++) {
            boards[j][i].position = sf::Vector2f(window_coordinate_x(board_profile[i].x()), window_coordinate_y(board_profile[i].y()));
        }

        boards[j][BOARD_VERTICES_COUNT].position = boards[j][0].position;
    }
}

void Graphic_viewer::setup_start_asterism(const Asterism& asterism) {
    for (int j = 0; j < BOARDS_COUNT; j++) {
        start_asterism[j].setPointCount(100);
        start_asterism[j].setOrigin(ASTERISM_CIRCLE_RADIUS, ASTERISM_CIRCLE_RADIUS);
        start_asterism[j].setPosition(window_coordinate_x(asterism.get_ngs(j).x()), window_coordinate_y(asterism.get_ngs(j).y()));
        start_asterism[j].setOutlineThickness(0.);
        start_asterism[j].setFillColor(sf::Color::Green);
    }
}

void Graphic_viewer::setup_destination_asterism(const Asterism& asterism) {
    for (int j = 0; j < BOARDS_COUNT; j++) {
        destination_asterism[j].setPointCount(100);
        destination_asterism[j].setOrigin(ASTERISM_CIRCLE_RADIUS, ASTERISM_CIRCLE_RADIUS);
        destination_asterism[j].setPosition(window_coordinate_x(asterism.get_ngs(j).x()), window_coordinate_y(asterism.get_ngs(j).y()));
        destination_asterism[j].setOutlineThickness(0.);
        destination_asterism[j].setFillColor(sf::Color::Red);
    }
}

void Graphic_viewer::rotate_clockwise_around_center(sf::ConvexShape& shape, float angle_degrees) {
    sf::Vector2f rotation_center(window_coordinate_x(0.), window_coordinate_y(0.));

    sf::Transform t;
    t.rotate(angle_degrees, rotation_center);

    sf::Vector2f new_position = t.transformPoint(shape.getPosition());

    shape.setPosition(new_position);
    shape.rotate(angle_degrees);
}

void Graphic_viewer::draw(const Board_set& board_set) {
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "", sf::Style::Close | sf::Style::Titlebar);
    setup_boards(board_set);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(technical_field);

        for (int j = 0; j < BOARDS_COUNT; j++) {
            window.draw(pom_ranges[j]);
            window.draw(boards[j]);
        }

        window.display();
    }
}

void Graphic_viewer::draw(const Board_set& board_set, const Asterism& asterism) {
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "", sf::Style::Close | sf::Style::Titlebar);
    setup_start_asterism(asterism);
    setup_boards(board_set);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(technical_field);

        for (int j = 0; j < BOARDS_COUNT; j++) {
            window.draw(pom_ranges[j]);
            window.draw(boards[j]);
            window.draw(start_asterism[j]);
        }

        window.display();
    }
}

void Graphic_viewer::draw(const Board_set& board_set, const Asterism& start, const Asterism& destination) {
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "", sf::Style::Close | sf::Style::Titlebar);
    setup_start_asterism(start);
    setup_destination_asterism(destination);
    setup_boards(board_set);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(technical_field);

        for (int j = 0; j < BOARDS_COUNT; j++) {
            window.draw(pom_ranges[j]);
            window.draw(boards[j]);
            window.draw(start_asterism[j]);
            window.draw(destination_asterism[j]);
        }

        window.display();
    }
}

