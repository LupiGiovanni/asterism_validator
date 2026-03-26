//
// Created by gionimbus on 12/16/25.
//

#include "Asterism.h"

Asterism::Asterism(): points ( { Point(0.,0.), Point(0.,0.), Point(0.,0.) } ) {}

Asterism::Asterism(double point0_x, double point1_x, double point2_x, double point0_y, double point1_y, double point2_y):
    points{ Point(point0_x, point0_y), Point(point1_x, point1_y), Point(point2_x, point2_y) } {}

Asterism::Asterism(const std::vector<Point>& points): points (points) {}

std::vector<Point> Asterism::get_points() const {
    return points;
}

void Asterism::set_points(const std::vector<Point>& new_points) {
    if (new_points.size() == BOARDS_COUNT)
        points = new_points;
    else
        std::cout << "Warning: attempted to run Asterism::set_points but 'new_points' vector has size != 3" << std::endl;
}

const Point& Asterism::operator[] (int index) const {
    return points[index];
}

bool Asterism::operator== (const Asterism& other) const {
    constexpr int points_count = 3;
    for (int i = 0; i < points_count; i++) {
        if ( ! is_equal_double(points[i].x(), other.points[i].x()) || ! is_equal_double(points[i].y(), other.points[i].y()) )
            return false;
    }
    return true;
}

void Asterism::print () const {
    std::cout << std::fixed << std::setprecision(DECIMAL_PLACES_PRINTED);
    std::cout << "{" << points[0].x() << ", " << points[1].x() << ", " << points[2].x() << ", " << points[0].y() << ", " << points[1].y() << ", " << points[2].y() << "}";
    std::cout << std::endl;
}

void Asterism::print_xy () const {
    std::cout << std::fixed << std::setprecision(DECIMAL_PLACES_PRINTED);
    std::cout << "(" << points[0].x() << ", " << points[0].y() << "), (" << points[1].x() << ", " << points[1].y() << "), (" << points[2].x() << ", " << points[2].y() << ")";
    std::cout << std::endl;
}