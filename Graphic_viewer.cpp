//
// Created by gionimbus on 1/26/26.
//

#include "Graphic_viewer.h"

Graphic_viewer::Graphic_viewer () {
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

    movement_delay = sf::milliseconds(MOVEMENT_DELAY);
    animation_delay = sf::milliseconds(ANIMATION_START_DELAY);
}

double Graphic_viewer::transform_into_window_x (double x_coordinate) const {
    return x_coordinate + WINDOW_WIDTH / 2.;
}

double Graphic_viewer::transform_into_window_y (double y_coordinate) const {
    return -y_coordinate + WINDOW_HEIGHT / 2.;
}

void Graphic_viewer::setup_pom_ranges () {
    pom_ranges[0].setPoint(0, sf::Vector2f(transform_into_window_x(coordinates::N1.x()), transform_into_window_y(coordinates::N1.y())));
    pom_ranges[0].setPoint(1, sf::Vector2f(transform_into_window_x(coordinates::O1.x()), transform_into_window_y(coordinates::O1.y())));
    pom_ranges[0].setPoint(2, sf::Vector2f(transform_into_window_x(coordinates::P1.x()), transform_into_window_y(coordinates::P1.y())));
    pom_ranges[0].setPoint(3, sf::Vector2f(transform_into_window_x(coordinates::Q1.x()), transform_into_window_y(coordinates::Q1.y())));
    pom_ranges[0].setOutlineThickness(0.);
    pom_ranges[0].setFillColor(sf::Color(255, 0, 0, CONVEX_SHAPES_TRANSPARENCY));

    pom_ranges[1].setPoint(0, sf::Vector2f(transform_into_window_x(coordinates::N2.x()), transform_into_window_y(coordinates::N2.y())));
    pom_ranges[1].setPoint(1, sf::Vector2f(transform_into_window_x(coordinates::O2.x()), transform_into_window_y(coordinates::O2.y())));
    pom_ranges[1].setPoint(2, sf::Vector2f(transform_into_window_x(coordinates::P2.x()), transform_into_window_y(coordinates::P2.y())));
    pom_ranges[1].setPoint(3, sf::Vector2f(transform_into_window_x(coordinates::Q2.x()), transform_into_window_y(coordinates::Q2.y())));
    pom_ranges[1].setOutlineThickness(0.);
    pom_ranges[1].setFillColor(sf::Color(0, 255, 0, CONVEX_SHAPES_TRANSPARENCY));

    pom_ranges[2].setPoint(0, sf::Vector2f(transform_into_window_x(coordinates::N3.x()), transform_into_window_y(coordinates::N3.y())));
    pom_ranges[2].setPoint(1, sf::Vector2f(transform_into_window_x(coordinates::O3.x()), transform_into_window_y(coordinates::O3.y())));
    pom_ranges[2].setPoint(2, sf::Vector2f(transform_into_window_x(coordinates::P3.x()), transform_into_window_y(coordinates::P3.y())));
    pom_ranges[2].setPoint(3, sf::Vector2f(transform_into_window_x(coordinates::Q3.x()), transform_into_window_y(coordinates::Q3.y())));
    pom_ranges[2].setOutlineThickness(0.);
    pom_ranges[2].setFillColor(sf::Color(0, 0, 255, CONVEX_SHAPES_TRANSPARENCY));

    for (auto& it : pom_ranges)
        rotate_clockwise_around_center(it, -90.f);
}

void Graphic_viewer::setup_fov_large () {
    fov_large.setPointCount(4);
    fov_large.setPoint(0, sf::Vector2f(transform_into_window_x(coordinates::R.x()), transform_into_window_y(coordinates::R.y())));
    fov_large.setPoint(1, sf::Vector2f(transform_into_window_x(coordinates::S.x()), transform_into_window_y(coordinates::S.y())));
    fov_large.setPoint(2, sf::Vector2f(transform_into_window_x(coordinates::T.x()), transform_into_window_y(coordinates::T.y())));
    fov_large.setPoint(3, sf::Vector2f(transform_into_window_x(coordinates::U.x()), transform_into_window_y(coordinates::U.y())));
    fov_large.setOutlineThickness(0.);
    fov_large.setFillColor(sf::Color(255, 255, 255, CONVEX_SHAPES_TRANSPARENCY));
}

void Graphic_viewer::setup_fov_small () {
    fov_small.setPointCount(4);
    fov_small.setPoint(0, sf::Vector2f(transform_into_window_x(coordinates::V.x()), transform_into_window_y(coordinates::V.y())));
    fov_small.setPoint(1, sf::Vector2f(transform_into_window_x(coordinates::W.x()), transform_into_window_y(coordinates::W.y())));
    fov_small.setPoint(2, sf::Vector2f(transform_into_window_x(coordinates::X.x()), transform_into_window_y(coordinates::X.y())));
    fov_small.setPoint(3, sf::Vector2f(transform_into_window_x(coordinates::Y.x()), transform_into_window_y(coordinates::Y.y())));
    fov_small.setOutlineThickness(0.);
    fov_small.setFillColor(sf::Color(255, 255, 255, CONVEX_SHAPES_TRANSPARENCY));
}

void Graphic_viewer::setup_technical_field () {
    technical_field.setPointCount(100);
    technical_field.setRadius(TECHNICAL_FIELD_RADIUS);
    technical_field.setOrigin(TECHNICAL_FIELD_RADIUS, TECHNICAL_FIELD_RADIUS);
    technical_field.setPosition(transform_into_window_x(0.), transform_into_window_y(0.));
    technical_field.setOutlineThickness(0.);
    technical_field.setFillColor(sf::Color(255, 255, 255, CONVEX_SHAPES_TRANSPARENCY));
}

void Graphic_viewer::setup_boards (const Board_set& board_set) {
    std::vector<Board> boards_vector = board_set.get_boards();

    for (int j = 0; j < BOARDS_COUNT; j++) {

        const Polygon& board_profile = boards_vector[j].get_profile();

        for (int i = 0; i < BOARD_VERTICES_COUNT; i++) {
            boards[j][i].position = sf::Vector2f(transform_into_window_x(board_profile[i].x()), transform_into_window_y(board_profile[i].y()));
        }

        boards[j][BOARD_VERTICES_COUNT].position = boards[j][0].position;
    }
}

void Graphic_viewer::setup_start_asterism (const Asterism& asterism) {
    for (int j = 0; j < BOARDS_COUNT; j++) {
        start_asterism[j].setPointCount(100);
        start_asterism[j].setOrigin(ASTERISM_CIRCLE_RADIUS, ASTERISM_CIRCLE_RADIUS);
        start_asterism[j].setPosition(transform_into_window_x(asterism.get_ngs(j).x()), transform_into_window_y(asterism.get_ngs(j).y()));
        start_asterism[j].setOutlineThickness(2);
        start_asterism[j].setOutlineColor(sf::Color::Black);
        start_asterism[j].setFillColor(sf::Color::Green);
    }
}

void Graphic_viewer::setup_destination_asterism (const Asterism& asterism) {
    for (int j = 0; j < BOARDS_COUNT; j++) {
        destination_asterism[j].setPointCount(100);
        destination_asterism[j].setOrigin(ASTERISM_CIRCLE_RADIUS, ASTERISM_CIRCLE_RADIUS);
        destination_asterism[j].setPosition(transform_into_window_x(asterism.get_ngs(j).x()), transform_into_window_y(asterism.get_ngs(j).y()));
        destination_asterism[j].setOutlineThickness(2);
        destination_asterism[j].setOutlineColor(sf::Color::Black);
        destination_asterism[j].setFillColor(sf::Color::Red);
    }
}

void Graphic_viewer::rotate_clockwise_around_center (sf::ConvexShape& shape, float angle_degrees) {
    sf::Vector2f rotation_center(transform_into_window_x(0.), transform_into_window_y(0.));

    sf::Transform t;
    t.rotate(angle_degrees, rotation_center);

    sf::Vector2f new_position = t.transformPoint(shape.getPosition());

    shape.setPosition(new_position);
    shape.rotate(angle_degrees);
}

void Graphic_viewer::draw (const Board_set& board_set) {
    sf::RenderWindow window;
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "", sf::Style::Close | sf::Style::Titlebar);
    setup_boards(board_set);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
        }

        window.clear(sf::Color::Black);
        window.draw(technical_field);
        window.draw(fov_large);
        window.draw(fov_small);

        for (int j = 0; j < BOARDS_COUNT; j++) {
            window.draw(pom_ranges[j]);
            window.draw(boards[j]);
        }

        window.display();
    }
}

void Graphic_viewer::draw (const Board_set& board_set, const Asterism& asterism) {
    sf::RenderWindow window;
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "", sf::Style::Close | sf::Style::Titlebar);
    setup_start_asterism(asterism);
    setup_boards(board_set);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
        }

        window.clear(sf::Color::Black);
        window.draw(technical_field);
        window.draw(fov_large);
        window.draw(fov_small);

        for (int j = 0; j < BOARDS_COUNT; j++) {
            window.draw(pom_ranges[j]);
            window.draw(boards[j]);
            window.draw(start_asterism[j]);
        }

        window.display();
    }
}

void Graphic_viewer::draw (const Board_set& board_set, const Asterism& start, const Asterism& destination) {
    sf::RenderWindow window;
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "", sf::Style::Close | sf::Style::Titlebar);
    setup_start_asterism(start);
    setup_destination_asterism(destination);
    setup_boards(board_set);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
        }

        window.clear(sf::Color::Black);
        window.draw(technical_field);
        window.draw(fov_large);
        window.draw(fov_small);

        for (int j = 0; j < BOARDS_COUNT; j++) {
            window.draw(pom_ranges[j]);
            window.draw(boards[j]);
            window.draw(start_asterism[j]);
            window.draw(destination_asterism[j]);
        }

        window.display();
    }
}

void Graphic_viewer::draw (const Asterism& start, const Asterism& destination) {
    sf::RenderWindow window;
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "", sf::Style::Close | sf::Style::Titlebar);
    setup_start_asterism(start);
    setup_destination_asterism(destination);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
        }

        window.clear(sf::Color::Black);
        window.draw(technical_field);
        window.draw(fov_large);
        window.draw(fov_small);

        for (int j = 0; j < BOARDS_COUNT; j++) {
            window.draw(pom_ranges[j]);
            window.draw(start_asterism[j]);
            window.draw(destination_asterism[j]);
        }

        window.display();
    }
}

void Graphic_viewer::animate (Movement movement_type, const Asterism& start, const Asterism& destination) {
    switch (movement_type) {
        case Movement::linear:
            animate_linear(start, destination);
            break;
        case Movement::safe_basic:
            animate_safe_basic(start, destination);
            break;
        case Movement::outside_technical_field:
            animate_outside_tech_field(start);
            break;
        case Movement::A_star:
            animate_A_star(start, destination);
            break;
        case Movement::none:
            std::cout << "Warning: attempted to run Graphic_viewer::animate but movement type is 'none'" << std::endl;
            break;
    }
}

void Graphic_viewer::animate_outside_tech_field (const Asterism &start) {
    sf::RenderWindow window;
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "", sf::Style::Close | sf::Style::Titlebar);

    Board_set temporary;
    temporary.assign_targets(start);

    if ( temporary.get_targets().empty() ) {
        std::cout << "Warning: attempted to run Graphic_viewer::animate_outside_tech_field but start asterism is invalid" << std::endl;
        window.close();
        return;
    }

    setup_start_asterism(start);

    while (window.isOpen()) {

        sf::Event event;

        if (animation_clock.getElapsedTime() >= animation_delay) {
            int iterations = 0;
            bool collision_detected = false;
            temporary.teleport(start);

            while ( temporary.is_in_technical_field() && ! collision_detected && iterations <= MAX_ITERATION_INDEX ) {

                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        return;
                    }
                }

                if (movement_clock.getElapsedTime() >= movement_delay) {
                    setup_boards(temporary);
                    window.clear(sf::Color::Black);
                    window.draw(technical_field);
                    window.draw(fov_large);
                    window.draw(fov_small);
                    for (int j = 0; j < BOARDS_COUNT; j++) {
                        window.draw(pom_ranges[j]);
                        window.draw(boards[j]);
                        window.draw(start_asterism[j]);
                    }
                    window.display();

                    temporary.move_outside_tech_field(SIMULATION_DISTANCE_STEP);
                    if (temporary.detect_collision()) {
                        collision_detected = true;
                    }
                    iterations += 1;
                    movement_clock.restart();
                } else sf::sleep(sf::milliseconds(1));
            }
            animation_clock.restart();
        } else sf::sleep(sf::milliseconds(10));
    }
}

void Graphic_viewer::animate_linear (const Asterism& start, const Asterism& destination) {
    sf::RenderWindow window;
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "", sf::Style::Close | sf::Style::Titlebar);

    bool start_valid = false;
    bool destination_valid = false;

    Board_set temporary;
    temporary.assign_targets(start);
    if ( ! temporary.get_targets().empty() ) {
        start_valid = true;
    }

    temporary.assign_targets(destination);
    if ( ! temporary.get_targets().empty() ) {
        destination_valid = true;
    }

    if ( ! start_valid || ! destination_valid ) {
        std::cout << "Warning: attempted to run Graphic_viewer::animate_linear but start or destination asterism are invalid" << std::endl;
        window.close();
        return;
    }

    setup_start_asterism(start);
    setup_destination_asterism(destination);

    while (window.isOpen()) {

        sf::Event event;

        if (animation_clock.getElapsedTime() >= animation_delay) {
            int iterations = 0;
            bool collision_detected = false;
            temporary.assign_targets(start);
            temporary.teleport(start);
            temporary.assign_targets(destination);

            while ( ! temporary.is_destination_reached(destination) && ! collision_detected && iterations <= MAX_ITERATION_INDEX ) {

                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        return;
                    }
                }

                if (movement_clock.getElapsedTime() >= movement_delay) {
                    setup_boards(temporary);
                    window.clear(sf::Color::Black);
                    window.draw(technical_field);
                    window.draw(fov_large);
                    window.draw(fov_small);
                    for (int j = 0; j < BOARDS_COUNT; j++) {
                        window.draw(pom_ranges[j]);
                        window.draw(boards[j]);
                        window.draw(start_asterism[j]);
                        window.draw(destination_asterism[j]);
                    }
                    window.display();

                    temporary.move(destination, SIMULATION_DISTANCE_STEP);
                    if (temporary.detect_collision()) {
                        collision_detected = true;
                    }
                    iterations += 1;
                    movement_clock.restart();
                } else sf::sleep(sf::milliseconds(1));
            }
            animation_clock.restart();
        } else sf::sleep(sf::milliseconds(10));
    }
}

void Graphic_viewer::animate_safe_basic (const Asterism& start, const Asterism& destination) {
    sf::RenderWindow window;
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "", sf::Style::Close | sf::Style::Titlebar);

    bool start_valid = false;
    bool destination_valid = false;

    Board_set temporary;
    temporary.assign_targets(start);
    if ( ! temporary.get_targets().empty() ) {
        start_valid = true;
        temporary.teleport(start);
    }

    temporary.assign_targets(destination);
    if ( ! temporary.get_targets().empty() ) {
        destination_valid = true;
    }

    if ( ! start_valid || ! destination_valid ) {
        std::cout << "Warning: attempted to run Graphic_viewer::animate_safe_basic but start or destination asterism are invalid" << std::endl;
        window.close();
        return;
    }

    setup_start_asterism(start);
    setup_destination_asterism(destination);

    while (window.isOpen()) {

        sf::Event event;

        if (animation_clock.getElapsedTime() >= animation_delay) {
            int iterations = 0;
            bool collision_detected = false;
            temporary.assign_targets(start);
            temporary.teleport(start);
            temporary.assign_targets(destination);

            while ( ! temporary.is_in_safe_zone() && ! collision_detected && iterations <= MAX_ITERATION_INDEX ) {

                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        return;
                    }
                }

                if (movement_clock.getElapsedTime() >= movement_delay) {
                    setup_boards(temporary);
                    window.clear(sf::Color::Black);
                    window.draw(technical_field);
                    window.draw(fov_large);
                    window.draw(fov_small);
                    for (int j = 0; j < BOARDS_COUNT; j++) {
                        window.draw(pom_ranges[j]);
                        window.draw(boards[j]);
                        window.draw(start_asterism[j]);
                        window.draw(destination_asterism[j]);
                    }
                    window.display();

                    temporary.move_to_safe_zone(SIMULATION_DISTANCE_STEP);
                    if (temporary.detect_collision()) {
                        collision_detected = true;
                    }
                    iterations += 1;
                    movement_clock.restart();
                } else sf::sleep(sf::milliseconds(1));
            }

            while ( ! temporary.is_destination_aligned_x(destination) && ! collision_detected && iterations <= MAX_ITERATION_INDEX ) {

                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        return;
                    }
                }

                if (movement_clock.getElapsedTime() >= movement_delay) {
                    setup_boards(temporary);
                    window.clear(sf::Color::Black);
                    window.draw(technical_field);
                    window.draw(fov_large);
                    window.draw(fov_small);
                    for (int j = 0; j < BOARDS_COUNT; j++) {
                        window.draw(pom_ranges[j]);
                        window.draw(boards[j]);
                        window.draw(start_asterism[j]);
                        window.draw(destination_asterism[j]);
                    }
                    window.display();

                    temporary.move_along_x(destination, SIMULATION_DISTANCE_STEP);
                    if (temporary.detect_collision()) {
                        collision_detected = true;
                    }
                    iterations += 1;
                    movement_clock.restart();
                } else sf::sleep(sf::milliseconds(1));
            }

            while ( ! temporary.is_destination_reached(destination, TOLERANCE * sqrt(2.)) && ! collision_detected && iterations <= MAX_ITERATION_INDEX ) {

                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        return;
                    }
                }

                if (movement_clock.getElapsedTime() >= movement_delay) {
                    setup_boards(temporary);
                    window.clear(sf::Color::Black);
                    window.draw(technical_field);
                    window.draw(fov_large);
                    window.draw(fov_small);
                    for (int j = 0; j < BOARDS_COUNT; j++) {
                        window.draw(pom_ranges[j]);
                        window.draw(boards[j]);
                        window.draw(start_asterism[j]);
                        window.draw(destination_asterism[j]);
                    }
                    window.display();

                    temporary.move_along_y(destination, SIMULATION_DISTANCE_STEP);
                    if (temporary.detect_collision()) {
                        collision_detected = true;
                    }
                    iterations += 1;
                    movement_clock.restart();
                } else sf::sleep(sf::milliseconds(1));
            }
            animation_clock.restart();
        } else sf::sleep(sf::milliseconds(10));
    }
}

void Graphic_viewer::animate_A_star (const Asterism& start, const Asterism& destination) {

    State state_start = transform_into_state (start);
    State state_goal =  transform_into_state (destination);

    const std::vector<State>& path = A_star::search_octile (state_start, state_goal);

    if (path.empty()) {
        std::cout << "Warning: attempted to run Graphic_viewer::animate_A_star but no path was found" << std::endl;
        return;
    }

    sf::RenderWindow window;
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "", sf::Style::Close | sf::Style::Titlebar);

    bool start_valid = false;
    bool destination_valid = false;

    Board_set temporary;
    temporary.assign_targets(start);
    if ( ! temporary.get_targets().empty() ) {
        start_valid = true;
        temporary.teleport(start);
    }

    temporary.assign_targets(destination);
    if ( ! temporary.get_targets().empty() ) {
        destination_valid = true;
    }

    if ( ! start_valid || ! destination_valid ) {
        std::cout << "Warning: attempted to run Graphic_viewer::animate_A_star but start or destination asterism are invalid" << std::endl;
        window.close();
        return;
    }

    setup_start_asterism(start);
    setup_destination_asterism(destination);

    Asterism current_destination;
    const std::vector<int>& targets = A_star::assign_targets(state_goal);

    while (window.isOpen()) {

        sf::Event event;

        if (animation_clock.getElapsedTime() >= animation_delay) {
            int iterations = 0;
            bool collision_detected = false;
            temporary.assign_targets(start);
            temporary.teleport(start);
            temporary.set_targets(targets);

            for (int i = 0; i < path.size(); i++) {
                if (collision_detected)
                    break;

                current_destination = transform_into_asterism (path[i]);

                while ( ! temporary.is_destination_reached(current_destination) && ! collision_detected && iterations <= MAX_ITERATION_INDEX ) {

                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                            window.close();
                            return;
                        }
                    }

                    if (movement_clock.getElapsedTime() >= movement_delay) {
                        setup_boards(temporary);
                        window.clear(sf::Color::Black);
                        window.draw(technical_field);
                        window.draw(fov_large);
                        window.draw(fov_small);
                        for (int j = 0; j < BOARDS_COUNT; j++) {
                            window.draw(pom_ranges[j]);
                            window.draw(boards[j]);
                            window.draw(start_asterism[j]);
                            window.draw(destination_asterism[j]);
                        }
                        window.display();

                        temporary.move(current_destination, SIMULATION_DISTANCE_STEP);
                        if ( temporary.detect_collision() ) {
                            collision_detected = true;
                        }
                        iterations += 1;
                        movement_clock.restart();
                    } else sf::sleep(sf::milliseconds(1));
                }
            }
            animation_clock.restart();
        } else sf::sleep(sf::milliseconds(10));
    }
}
