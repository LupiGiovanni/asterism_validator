//
// Created by gionimbus on 12/16/25.
//

#include "Board.h"

Board::Board (Board_type type) {
    if (type == Board_type::type0)
    {
        profile.push_back(coordinates::A1);
        profile.push_back(coordinates::B1);
        profile.push_back(coordinates::C1);
        profile.push_back(coordinates::D1);
        profile.push_back(coordinates::E1);
        profile.push_back(coordinates::F1);
        profile.push_back(coordinates::G1);
        profile.push_back(coordinates::H1);
        profile.push_back(coordinates::I1);
        profile.push_back(coordinates::J1);
        profile.push_back(coordinates::K1);
        profile.push_back(coordinates::L1);

        pom = coordinates::M1;
        pom_home = coordinates::M1;

        pom_range.push_back(coordinates::N1);
        pom_range.push_back(coordinates::O1);
        pom_range.push_back(coordinates::P1);
        pom_range.push_back(coordinates::Q1);
    }
    else if (type == Board_type::type1)
    {
        profile.push_back(coordinates::A2);
        profile.push_back(coordinates::B2);
        profile.push_back(coordinates::C2);
        profile.push_back(coordinates::D2);
        profile.push_back(coordinates::E2);
        profile.push_back(coordinates::F2);
        profile.push_back(coordinates::G2);
        profile.push_back(coordinates::H2);
        profile.push_back(coordinates::I2);
        profile.push_back(coordinates::J2);
        profile.push_back(coordinates::K2);
        profile.push_back(coordinates::L2);

        pom = coordinates::M2;
        pom_home = coordinates::M2;

        pom_range.push_back(coordinates::N2);
        pom_range.push_back(coordinates::O2);
        pom_range.push_back(coordinates::P2);
        pom_range.push_back(coordinates::Q2);
    }
    else if (type == Board_type::type2)
    {
        profile.push_back(coordinates::A3);
        profile.push_back(coordinates::B3);
        profile.push_back(coordinates::C3);
        profile.push_back(coordinates::D3);
        profile.push_back(coordinates::E3);
        profile.push_back(coordinates::F3);
        profile.push_back(coordinates::G3);
        profile.push_back(coordinates::H3);
        profile.push_back(coordinates::I3);
        profile.push_back(coordinates::J3);
        profile.push_back(coordinates::K3);
        profile.push_back(coordinates::L3);

        pom = coordinates::M3;
        pom_home = coordinates::M3;

        pom_range.push_back(coordinates::N3);
        pom_range.push_back(coordinates::O3);
        pom_range.push_back(coordinates::P3);
        pom_range.push_back(coordinates::Q3);
    }

    // Rotation is needed to align the CAD reference system with ours
    rotate(profile, M_PI / 2.);
    rotate(pom, M_PI / 2.);
    rotate(pom_home, M_PI / 2.);
    rotate(pom_range, M_PI / 2.);
}

const Polygon& Board::get_profile() const {
    return profile;
}

bool Board::is_in_range (const Point& point) const {
    if (pom_range.bounded_side(point) == CGAL::ON_BOUNDED_SIDE || pom_range.bounded_side(point) == CGAL::ON_BOUNDARY)
        return true;
    return false;
}

bool Board::teleport (double delta_x, double delta_y) {
    Vector displacement (delta_x, delta_y);
    Point destination = pom + displacement;

    if (!is_in_range(destination))
        return false;

    for (auto it = profile.begin(); it != profile.end(); ++it)
        *it = *it + displacement;

    pom = destination;

    return true;
}

bool Board::teleport (const Point& pom_destination) {
    return teleport (pom_destination.x() - pom.x(), pom_destination.y() - pom.y());
}

void Board::teleport_home() {
    teleport(pom_home);
}

bool Board::is_destination_reached (const Point& pom_destination) const {
    Vector displacement (pom_destination - pom);
    double distance = std::sqrt(displacement.squared_length());
    if (distance <= TOLERANCE)
        return true;
    return false;
}

bool Board::is_in_technical_field (const Circle& technical_field) const {
    bool detected = false;

    for (auto it = profile.begin(); it != profile.end(); ++it) {
        if ((technical_field.bounded_side(*it) == CGAL::ON_BOUNDED_SIDE) || (technical_field.bounded_side(*it) == CGAL::ON_BOUNDARY)) {
            detected = true;
            break;
        }
    }

    return detected;
}

double Board::calculate_distance (const Point& pom_destination) const {
    Vector displacement (pom_destination - pom);
    return std::sqrt(displacement.squared_length());
}

bool Board::move (const Point& pom_destination, double distance_step) {
    if (is_destination_reached(pom_destination))
        return false;

    Vector displacement (pom_destination - pom);
    double length = std::sqrt(displacement.squared_length());
    Vector step_vector = (displacement / length) * distance_step;
    teleport (pom + step_vector);

    return true;
}

bool Board::move_outside_tech_field (const Circle& tech_field, double distance_step) {
    if (!is_in_technical_field(tech_field))
        return false;

    Point bottom_left_corner = *pom_range.begin();
    Point bottom_right_corner = *(pom_range.end() - 1);

    double distance_to_bottom_left_corner = calculate_distance(bottom_left_corner);
    double distance_to_bottom_right_corner = calculate_distance(bottom_right_corner);

    Vector displacement;
    if (distance_to_bottom_left_corner < distance_to_bottom_right_corner)
        displacement = bottom_left_corner - pom;
    else
        displacement = bottom_right_corner - pom;

    double length = std::sqrt(displacement.squared_length());
    Vector step_vector = (displacement / length) * distance_step;
    teleport (pom + step_vector);

    return true;
}