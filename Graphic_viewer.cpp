//
// Created by gionimbus on 1/26/26.
//

#include "Graphic_viewer.h"
#include "CAD_coordinates.h"

Graphic_viewer::Graphic_viewer () {
    for (int j = 0; j < BOARDS_COUNT; j++) {
        boards.push_back( sf::VertexArray(sf::LineStrip, BOARD_VERTICES_COUNT + 1) );
        trajectories.push_back(sf::VertexArray(sf::Points));
        pom_ranges.push_back(sf::ConvexShape(POM_RANGE_VERTICES_COUNT));
        start_asterism.push_back(sf::CircleShape(ASTERISM_CIRCLE_RADIUS));
        destination_asterism.push_back(sf::CircleShape(ASTERISM_CIRCLE_RADIUS));
    }

    setup_pom_ranges();
    clear_trajectories();
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
    pom_ranges[0].setPoint(0, sf::Vector2f(transform_into_window_x(CAD_coordinates::N1.x()), transform_into_window_y(CAD_coordinates::N1.y())));
    pom_ranges[0].setPoint(1, sf::Vector2f(transform_into_window_x(CAD_coordinates::O1.x()), transform_into_window_y(CAD_coordinates::O1.y())));
    pom_ranges[0].setPoint(2, sf::Vector2f(transform_into_window_x(CAD_coordinates::P1.x()), transform_into_window_y(CAD_coordinates::P1.y())));
    pom_ranges[0].setPoint(3, sf::Vector2f(transform_into_window_x(CAD_coordinates::Q1.x()), transform_into_window_y(CAD_coordinates::Q1.y())));
    pom_ranges[0].setOutlineThickness(0.);
    pom_ranges[0].setFillColor(sf::Color(255, 0, 0, CONVEX_SHAPES_TRANSPARENCY));

    pom_ranges[1].setPoint(0, sf::Vector2f(transform_into_window_x(CAD_coordinates::N2.x()), transform_into_window_y(CAD_coordinates::N2.y())));
    pom_ranges[1].setPoint(1, sf::Vector2f(transform_into_window_x(CAD_coordinates::O2.x()), transform_into_window_y(CAD_coordinates::O2.y())));
    pom_ranges[1].setPoint(2, sf::Vector2f(transform_into_window_x(CAD_coordinates::P2.x()), transform_into_window_y(CAD_coordinates::P2.y())));
    pom_ranges[1].setPoint(3, sf::Vector2f(transform_into_window_x(CAD_coordinates::Q2.x()), transform_into_window_y(CAD_coordinates::Q2.y())));
    pom_ranges[1].setOutlineThickness(0.);
    pom_ranges[1].setFillColor(sf::Color(0, 255, 0, CONVEX_SHAPES_TRANSPARENCY));

    pom_ranges[2].setPoint(0, sf::Vector2f(transform_into_window_x(CAD_coordinates::N3.x()), transform_into_window_y(CAD_coordinates::N3.y())));
    pom_ranges[2].setPoint(1, sf::Vector2f(transform_into_window_x(CAD_coordinates::O3.x()), transform_into_window_y(CAD_coordinates::O3.y())));
    pom_ranges[2].setPoint(2, sf::Vector2f(transform_into_window_x(CAD_coordinates::P3.x()), transform_into_window_y(CAD_coordinates::P3.y())));
    pom_ranges[2].setPoint(3, sf::Vector2f(transform_into_window_x(CAD_coordinates::Q3.x()), transform_into_window_y(CAD_coordinates::Q3.y())));
    pom_ranges[2].setOutlineThickness(0.);
    pom_ranges[2].setFillColor(sf::Color(0, 0, 255, CONVEX_SHAPES_TRANSPARENCY));

    for (auto& it : pom_ranges)
        rotate_clockwise_around_center(it, -90.f);
}

void Graphic_viewer::setup_fov_large () {
    fov_large.setPointCount(4);
    fov_large.setPoint(0, sf::Vector2f(transform_into_window_x(CAD_coordinates::R.x()), transform_into_window_y(CAD_coordinates::R.y())));
    fov_large.setPoint(1, sf::Vector2f(transform_into_window_x(CAD_coordinates::S.x()), transform_into_window_y(CAD_coordinates::S.y())));
    fov_large.setPoint(2, sf::Vector2f(transform_into_window_x(CAD_coordinates::T.x()), transform_into_window_y(CAD_coordinates::T.y())));
    fov_large.setPoint(3, sf::Vector2f(transform_into_window_x(CAD_coordinates::U.x()), transform_into_window_y(CAD_coordinates::U.y())));
    fov_large.setOutlineThickness(0.);
    fov_large.setFillColor(sf::Color(255, 255, 255, CONVEX_SHAPES_TRANSPARENCY));
}

void Graphic_viewer::setup_fov_small () {
    fov_small.setPointCount(4);
    fov_small.setPoint(0, sf::Vector2f(transform_into_window_x(CAD_coordinates::V.x()), transform_into_window_y(CAD_coordinates::V.y())));
    fov_small.setPoint(1, sf::Vector2f(transform_into_window_x(CAD_coordinates::W.x()), transform_into_window_y(CAD_coordinates::W.y())));
    fov_small.setPoint(2, sf::Vector2f(transform_into_window_x(CAD_coordinates::X.x()), transform_into_window_y(CAD_coordinates::X.y())));
    fov_small.setPoint(3, sf::Vector2f(transform_into_window_x(CAD_coordinates::Y.x()), transform_into_window_y(CAD_coordinates::Y.y())));
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
        start_asterism[j].setPosition(transform_into_window_x(asterism[j].x()), transform_into_window_y(asterism[j].y()));
        start_asterism[j].setOutlineThickness(2);
        start_asterism[j].setOutlineColor(sf::Color::Black);
        start_asterism[j].setFillColor(sf::Color::Green);
    }
}

void Graphic_viewer::setup_destination_asterism (const Asterism& asterism) {
    for (int j = 0; j < BOARDS_COUNT; j++) {
        destination_asterism[j].setPointCount(100);
        destination_asterism[j].setOrigin(ASTERISM_CIRCLE_RADIUS, ASTERISM_CIRCLE_RADIUS);
        destination_asterism[j].setPosition(transform_into_window_x(asterism[j].x()), transform_into_window_y(asterism[j].y()));
        destination_asterism[j].setOutlineThickness(2);
        destination_asterism[j].setOutlineColor(sf::Color::Black);
        destination_asterism[j].setFillColor(sf::Color::Red);
    }
}

void Graphic_viewer::clear_trajectories () {
    for (int j = 0; j < BOARDS_COUNT; j++)
        trajectories[j].clear();
}

void Graphic_viewer::update_trajectories (const Board_set& board_set) {
    std::vector<Board> b = board_set.get_boards();

    for (int j = 0; j < BOARDS_COUNT; j++) {
        Point pom_pos = b[j].get_pom_position();
        sf::Vertex v;

        v.position = sf::Vector2f(transform_into_window_x(pom_pos.x()), transform_into_window_y(pom_pos.y()));
        v.color = sf::Color::Green;
        v.color.a = 255;

        trajectories[j].append(v);
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

void Graphic_viewer::animate_outside_tech_field (const Asterism& start) {
    sf::RenderWindow window;
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "", sf::Style::Close | sf::Style::Titlebar);

    if ( ! start.is_valid() ) {
        std::cout << "Warning: attempted to run Graphic_viewer::animate_outside_tech_field but start asterism is invalid" << std::endl;
        window.close();
        return;
    }

    Board_set temporary;
    setup_start_asterism(start);

    while (window.isOpen()) {

        sf::Event event;

        if (animation_clock.getElapsedTime() >= animation_delay) {
            int iterations = 0;
            bool collision_detected = false;
            clear_trajectories();
            temporary.teleport_home();
            temporary.assign_targets(start);
            temporary.teleport(start);

            while ( temporary.is_in_technical_field() && ! collision_detected && iterations <= MAX_ITERATION_INDEX ) {

                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        return;
                    }
                }

                if (movement_clock.getElapsedTime() >= movement_delay) {
                    update_trajectories(temporary);
                    setup_boards(temporary);
                    window.clear(sf::Color::Black);
                    window.draw(technical_field);
                    window.draw(fov_large);
                    window.draw(fov_small);
                    for (int j = 0; j < BOARDS_COUNT; j++) {
                        window.draw(pom_ranges[j]);
                        window.draw(trajectories[j]);
                        window.draw(boards[j]);
                        window.draw(start_asterism[j]);
                    }
                    window.display();

                    temporary.step_move_outside_tech_field();
                    if (temporary.detect_collision()) {
                        collision_detected = true;
                        std::cout << "Collision detected during Graphic_viewer::animate_outside_tech_field" << std::endl;
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

    bool start_valid = start.is_valid();
    bool destination_valid = destination.is_valid();

    if ( ! start_valid || ! destination_valid ) {
        std::cout << "Warning: attempted to run Graphic_viewer::animate_linear but start or destination asterism are invalid" << std::endl;
        window.close();
        return;
    }

    Board_set temporary;
    setup_start_asterism(start);
    setup_destination_asterism(destination);

    while (window.isOpen()) {

        sf::Event event;

        if (animation_clock.getElapsedTime() >= animation_delay) {
            int iterations = 0;
            bool collision_detected = false;
            clear_trajectories();
            temporary.teleport_home();
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
                    update_trajectories(temporary);
                    setup_boards(temporary);
                    window.clear(sf::Color::Black);
                    window.draw(technical_field);
                    window.draw(fov_large);
                    window.draw(fov_small);
                    for (int j = 0; j < BOARDS_COUNT; j++) {
                        window.draw(pom_ranges[j]);
                        window.draw(trajectories[j]);
                        window.draw(boards[j]);
                        window.draw(start_asterism[j]);
                        window.draw(destination_asterism[j]);
                    }
                    window.display();

                    temporary.step_move(destination);
                    if (temporary.detect_collision()) {
                        collision_detected = true;
                        std::cout << "Collision detected during Graphic_viewer::animate_linear" << std::endl;
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

    bool start_valid = start.is_valid();
    bool destination_valid = destination.is_valid();

    if ( ! start_valid || ! destination_valid ) {
        std::cout << "Warning: attempted to run Graphic_viewer::animate_safe_basic but start or destination asterism are invalid" << std::endl;
        window.close();
        return;
    }

    Board_set temporary;
    setup_start_asterism(start);
    setup_destination_asterism(destination);

    while (window.isOpen()) {

        sf::Event event;

        if (animation_clock.getElapsedTime() >= animation_delay) {
            int iterations = 0;
            bool collision_detected = false;
            clear_trajectories();
            temporary.teleport_home();
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
                    update_trajectories(temporary);
                    setup_boards(temporary);
                    window.clear(sf::Color::Black);
                    window.draw(technical_field);
                    window.draw(fov_large);
                    window.draw(fov_small);
                    for (int j = 0; j < BOARDS_COUNT; j++) {
                        window.draw(pom_ranges[j]);
                        window.draw(boards[j]);
                        window.draw(trajectories[j]);
                        window.draw(start_asterism[j]);
                        window.draw(destination_asterism[j]);
                    }
                    window.display();

                    temporary.step_move_to_safe_zone();
                    if (temporary.detect_collision()) {
                        collision_detected = true;
                        std::cout << "Collision detected during Graphic_viewer::animate_safe_basic" << std::endl;
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
                    update_trajectories(temporary);
                    setup_boards(temporary);
                    window.clear(sf::Color::Black);
                    window.draw(technical_field);
                    window.draw(fov_large);
                    window.draw(fov_small);
                    for (int j = 0; j < BOARDS_COUNT; j++) {
                        window.draw(pom_ranges[j]);
                        window.draw(trajectories[j]);
                        window.draw(boards[j]);
                        window.draw(start_asterism[j]);
                        window.draw(destination_asterism[j]);
                    }
                    window.display();

                    temporary.step_move_along_x(destination);
                    if (temporary.detect_collision()) {
                        collision_detected = true;
                        std::cout << "Collision detected during Graphic_viewer::animate_safe_basic" << std::endl;
                    }
                    iterations += 1;
                    movement_clock.restart();
                } else sf::sleep(sf::milliseconds(1));
            }

            while ( ! temporary.is_destination_reached(destination, DESTINATION_REACHED_TOLERANCE * sqrt(2.)) && ! collision_detected && iterations <= MAX_ITERATION_INDEX ) {

                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        return;
                    }
                }

                if (movement_clock.getElapsedTime() >= movement_delay) {
                    update_trajectories(temporary);
                    setup_boards(temporary);
                    window.clear(sf::Color::Black);
                    window.draw(technical_field);
                    window.draw(fov_large);
                    window.draw(fov_small);
                    for (int j = 0; j < BOARDS_COUNT; j++) {
                        window.draw(pom_ranges[j]);
                        window.draw(trajectories[j]);
                        window.draw(boards[j]);
                        window.draw(start_asterism[j]);
                        window.draw(destination_asterism[j]);
                    }
                    window.display();

                    temporary.step_move_along_y(destination);
                    if (temporary.detect_collision()) {
                        collision_detected = true;
                        std::cout << "Collision detected during Graphic_viewer::animate_safe_basic" << std::endl;
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
    bool start_valid = start.is_valid();
    bool destination_valid = destination.is_valid();

    if (!start_valid || !destination_valid) {
        std::cout << "Warning: attempted to run Graphic_viewer::animate_A_star but start or destination asterism are invalid" << std::endl;
        return;
    }

    if ( FOV_OPTIONS == Fov_options::fov_small_excluded && ( start.is_in_fov_small() || destination.is_in_fov_small() ) ) {
        std::cout << "Warning: attempted to run Simulation::run_A_star with FOV_OPTIONS set to 'fov_small_excluded' but start and/or destination asterisms are in small FoV" << std::endl;
        return;
    }

    if ( FOV_OPTIONS == Fov_options::fov_large_excluded && ( start.is_in_fov_large() || destination.is_in_fov_large() ) ) {
        std::cout << "Warning: attempted to run Simulation::run_A_star with FOV_OPTIONS set to 'fov_large_excluded' but start and/or destination asterisms are in large FoV" << std::endl;
        return;
    }

    State s = start;
    State d =  destination;
    std::vector<State> path;

    if constexpr (GRID_TYPE == Grid_type::isometric) {
        if constexpr (FOV_OPTIONS == Fov_options::none)
            path = A_star::search_isometric (s, d, A_star::is_valid_state);
        else if constexpr (FOV_OPTIONS == Fov_options::fov_small_excluded)
            path = A_star::search_isometric (s, d, A_star::is_valid_state_fov_small_excluded);
        else if constexpr (FOV_OPTIONS == Fov_options::fov_large_excluded)
            path = A_star::search_isometric (s, d, A_star::is_valid_state_fov_large_excluded);
    }

    if constexpr (GRID_TYPE == Grid_type::manhattan) {
        if constexpr (FOV_OPTIONS == Fov_options::none)
            path = A_star::search_manhattan (s, d, A_star::is_valid_state);
        else if constexpr (FOV_OPTIONS == Fov_options::fov_small_excluded)
            path = A_star::search_manhattan (s, d, A_star::is_valid_state_fov_small_excluded);
        else if constexpr (FOV_OPTIONS == Fov_options::fov_large_excluded)
            path = A_star::search_manhattan (s, d, A_star::is_valid_state_fov_large_excluded);
    }

    if (path.empty()) {
        std::cout << "Warning: attempted to run Graphic_viewer::animate_A_star but no path was found" << std::endl;
        return;
    }

    for (int i = 0; i < path.size(); i++) {
        std::cout << "State " << i << ":\t";
        path[i].print_xy();
        std::cout << std::endl;
    }
    std::cout << std::endl;

    sf::RenderWindow window;
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "", sf::Style::Close | sf::Style::Titlebar);

    Board_set temporary;
    State current_destination;
    setup_start_asterism(s);
    setup_destination_asterism(d);

    while (window.isOpen()) {

        sf::Event event;

        if (animation_clock.getElapsedTime() >= animation_delay) {
            int iterations = 0;
            bool collision_detected = false;
            clear_trajectories();
            temporary.teleport_home();
            temporary.assign_targets(s);
            temporary.teleport(s);
            temporary.assign_targets(d);

            for (int i = 1; i < path.size(); i++) {
                if (collision_detected)
                    break;

                current_destination = path[i];

                while ( ! temporary.is_destination_reached(current_destination) && ! collision_detected && iterations <= MAX_ITERATION_INDEX ) {

                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                            window.close();
                            return;
                        }
                    }

                    if (movement_clock.getElapsedTime() >= movement_delay) {
                        update_trajectories(temporary);
                        setup_boards(temporary);
                        window.clear(sf::Color::Black);
                        window.draw(technical_field);
                        window.draw(fov_large);
                        window.draw(fov_small);
                        for (int j = 0; j < BOARDS_COUNT; j++) {
                            window.draw(pom_ranges[j]);
                            window.draw(trajectories[j]);
                            window.draw(boards[j]);
                            window.draw(start_asterism[j]);
                            window.draw(destination_asterism[j]);
                        }
                        window.display();

                        temporary.step_move(current_destination);
                        if ( temporary.detect_collision() ) {
                            collision_detected = true;
                            std::cout << "Collision detected during Graphic_viewer::animate_A_star" << std::endl;
                        }
                        iterations += 1;
                        movement_clock.restart();
                    } else sf::sleep(sf::milliseconds(1));
                }
            }

            while ( ! temporary.is_destination_reached(d) && ! collision_detected && iterations <= MAX_ITERATION_INDEX ) {

                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        return;
                    }
                }

                if (movement_clock.getElapsedTime() >= movement_delay) {
                    update_trajectories(temporary);
                    setup_boards(temporary);
                    window.clear(sf::Color::Black);
                    window.draw(technical_field);
                    window.draw(fov_large);
                    window.draw(fov_small);
                    for (int j = 0; j < BOARDS_COUNT; j++) {
                        window.draw(pom_ranges[j]);
                        window.draw(trajectories[j]);
                        window.draw(boards[j]);
                        window.draw(start_asterism[j]);
                        window.draw(destination_asterism[j]);
                    }
                    window.display();

                    temporary.step_move(d);
                    if ( temporary.detect_collision() ) {
                        collision_detected = true;
                        std::cout << "Collision detected during Graphic_viewer::animate_A_star" << std::endl;
                    }
                    iterations += 1;
                    movement_clock.restart();
                } else sf::sleep(sf::milliseconds(1));
            }
            animation_clock.restart();
        } else sf::sleep(sf::milliseconds(10));
    }
}