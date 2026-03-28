//
// Created by gionimbus on 12/16/25.
//

#include "Board.h"
#include "CAD_coordinates.h"

Board::Board (Board_type type) {
    if (type == Board_type::type0)
    {
        profile.push_back(CAD_coordinates::A1);
        profile.push_back(CAD_coordinates::B1);
        profile.push_back(CAD_coordinates::C1);
        profile.push_back(CAD_coordinates::D1);
        profile.push_back(CAD_coordinates::E1);
        profile.push_back(CAD_coordinates::F1);
        profile.push_back(CAD_coordinates::G1);
        profile.push_back(CAD_coordinates::H1);
        profile.push_back(CAD_coordinates::I1);
        profile.push_back(CAD_coordinates::J1);
        profile.push_back(CAD_coordinates::K1);
        profile.push_back(CAD_coordinates::L1);

        pom = CAD_coordinates::M1;
        pom_home = CAD_coordinates::M1;

        pom_range.push_back(CAD_coordinates::N1);
        pom_range.push_back(CAD_coordinates::O1);
        pom_range.push_back(CAD_coordinates::P1);
        pom_range.push_back(CAD_coordinates::Q1);

        pom_safe_zone.push_back(CAD_coordinates::N1);
        pom_safe_zone.push_back(CAD_coordinates::Z1);
        pom_safe_zone.push_back(CAD_coordinates::AA1);
        pom_safe_zone.push_back(CAD_coordinates::Q1);
    }
    else if (type == Board_type::type1)
    {
        profile.push_back(CAD_coordinates::A2);
        profile.push_back(CAD_coordinates::B2);
        profile.push_back(CAD_coordinates::C2);
        profile.push_back(CAD_coordinates::D2);
        profile.push_back(CAD_coordinates::E2);
        profile.push_back(CAD_coordinates::F2);
        profile.push_back(CAD_coordinates::G2);
        profile.push_back(CAD_coordinates::H2);
        profile.push_back(CAD_coordinates::I2);
        profile.push_back(CAD_coordinates::J2);
        profile.push_back(CAD_coordinates::K2);
        profile.push_back(CAD_coordinates::L2);

        pom = CAD_coordinates::M2;
        pom_home = CAD_coordinates::M2;

        pom_range.push_back(CAD_coordinates::N2);
        pom_range.push_back(CAD_coordinates::O2);
        pom_range.push_back(CAD_coordinates::P2);
        pom_range.push_back(CAD_coordinates::Q2);

        pom_safe_zone.push_back(CAD_coordinates::N2);
        pom_safe_zone.push_back(CAD_coordinates::Z2);
        pom_safe_zone.push_back(CAD_coordinates::AA2);
        pom_safe_zone.push_back(CAD_coordinates::Q2);
    }
    else if (type == Board_type::type2)
    {
        profile.push_back(CAD_coordinates::A3);
        profile.push_back(CAD_coordinates::B3);
        profile.push_back(CAD_coordinates::C3);
        profile.push_back(CAD_coordinates::D3);
        profile.push_back(CAD_coordinates::E3);
        profile.push_back(CAD_coordinates::F3);
        profile.push_back(CAD_coordinates::G3);
        profile.push_back(CAD_coordinates::H3);
        profile.push_back(CAD_coordinates::I3);
        profile.push_back(CAD_coordinates::J3);
        profile.push_back(CAD_coordinates::K3);
        profile.push_back(CAD_coordinates::L3);

        pom = CAD_coordinates::M3;
        pom_home = CAD_coordinates::M3;

        pom_range.push_back(CAD_coordinates::N3);
        pom_range.push_back(CAD_coordinates::O3);
        pom_range.push_back(CAD_coordinates::P3);
        pom_range.push_back(CAD_coordinates::Q3);

        pom_safe_zone.push_back(CAD_coordinates::N3);
        pom_safe_zone.push_back(CAD_coordinates::Z3);
        pom_safe_zone.push_back(CAD_coordinates::AA3);
        pom_safe_zone.push_back(CAD_coordinates::Q3);
    }

    profile_buffer_zone = enlarge(profile, BOARD_BUFFER_WIDTH);

    // Rotation is needed to align the CAD reference system with ours
    rotate(profile, M_PI / 2.);
    rotate(profile_buffer_zone, M_PI / 2.);
    rotate(pom, M_PI / 2.);
    rotate(pom_home, M_PI / 2.);
    rotate(pom_range, M_PI / 2.);
    rotate(pom_safe_zone, M_PI / 2.);
}

const Polygon& Board::get_profile () const {
    return profile;
}

const Point& Board::get_pom_position () const {
    return pom;
}

bool Board::is_in_range (const Point& point) const {
    if (pom_range.bounded_side(point) == CGAL::ON_BOUNDED_SIDE || pom_range.bounded_side(point) == CGAL::ON_BOUNDARY)
        return true;
    return false;
}

bool Board::teleport (double delta_x, double delta_y) {
    const Vector displacement(delta_x, delta_y);
    const Point destination = pom + displacement;

    if (!is_in_range(destination))
        return false;

    for (auto& point : profile)
        point += displacement;
    for (auto& point : profile_buffer_zone)
        point += displacement;

    pom = destination;

    return true;
}

bool Board::teleport (const Point& pom_destination) {
    return teleport (pom_destination.x() - pom.x(), pom_destination.y() - pom.y());
}

void Board::teleport_home () {
    teleport(pom_home);
}

bool Board::is_destination_reached (const Point& pom_destination, double tolerance) const {
    Vector displacement (pom_destination - pom);
    double distance = std::sqrt(displacement.squared_length());
    if (distance <= tolerance)
        return true;
    return false;
}

bool Board::is_destination_aligned_x (const Point& pom_destination) const {
    Point aligned_point_x = find_aligned_point_x(pom_destination);
    return is_destination_reached(aligned_point_x);
}

bool Board::is_destination_aligned_y (const Point& pom_destination) const {
    Point aligned_point_y = find_aligned_point_y(pom_destination);
    return is_destination_reached(aligned_point_y);
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

bool Board::is_in_safe_zone () const {
    if (pom_safe_zone.bounded_side(pom) == CGAL::ON_BOUNDED_SIDE)
        return true;
    return false;
}

double Board::calculate_distance (const Point& pom_destination) const {
    Vector displacement (pom_destination - pom);
    return std::sqrt(displacement.squared_length());
}

bool Board::move (const Point& pom_destination, double distance_step) {
    if (is_destination_reached(pom_destination))
        return false;

    Vector displacement (pom_destination - pom);
    double displacement_length = std::sqrt(displacement.squared_length());
    Vector step_vector = (displacement / displacement_length) * distance_step;
    teleport (pom + step_vector);

    return true;
}

bool Board::move_outside_tech_field (const Circle& tech_field, double distance_step) {
    if (!is_in_technical_field(tech_field))
        return false;

    Point bottom_left_corner = *pom_range.begin();
    Point bottom_right_corner = *(pom_range.end() - 1);

    Vector displacement;
    if ( calculate_distance(bottom_left_corner) < calculate_distance(bottom_right_corner) )
        displacement = bottom_left_corner - pom;
    else
        displacement = bottom_right_corner - pom;

    double displacement_length = std::sqrt(displacement.squared_length());
    Vector step_vector = (displacement / displacement_length) * distance_step;
    teleport (pom + step_vector);

    return true;
}

bool Board::move_along_x (const Point& pom_destination, double distance_step) {
    Point aligned_point_x = find_aligned_point_x(pom_destination);
    return move(aligned_point_x, distance_step);
}

bool Board::move_along_y (const Point& pom_destination, double distance_step) {
    Point aligned_point_y = find_aligned_point_y(pom_destination);
    return move(aligned_point_y, distance_step);
}

bool Board::move_to_safe_zone (double distance_step) {
    if (is_in_safe_zone())
        return false;

    Point centre (0., 0.);
    Vector v = pom_home - centre;
    double v_length = std::sqrt(v.squared_length());
    Vector step_vector = (v / v_length) * distance_step;
    return teleport(pom + step_vector);
}

Point Board::find_aligned_point_x (const Point& pom_destination) const {
    Point bottom_left_corner = *pom_range.begin();
    Point bottom_right_corner = *(pom_range.end() - 1);
    Vector horizontal_vector = bottom_left_corner - bottom_right_corner;

    Point centre (0., 0.);
    Vector vertical_vector = centre - pom_home;

    Line horizontal_line (pom, horizontal_vector);
    Line vertical_line (pom_destination, vertical_vector);

    auto intersection = CGAL::intersection(horizontal_line, vertical_line).value();
    return std::get<Point>(intersection);
}

Point Board::find_aligned_point_y (const Point& pom_destination) const {
    Point bottom_left_corner = *pom_range.begin();
    Point bottom_right_corner = *(pom_range.end() - 1);
    Vector horizontal_vector = bottom_left_corner - bottom_right_corner;

    Point centre (0., 0.);
    Vector vertical_vector = centre - pom_home;

    Line horizontal_line (pom_destination, horizontal_vector);
    Line vertical_line (pom, vertical_vector);

    auto intersection = CGAL::intersection(horizontal_line, vertical_line).value();
    return std::get<Point>(intersection);
}

