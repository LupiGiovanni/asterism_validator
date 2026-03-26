//
// Created by gionimbus on 12/16/25.
//

#ifndef ASTERISM_VALIDATOR_ASTERISM_H
#define ASTERISM_VALIDATOR_ASTERISM_H

#include "Board.h"

class Asterism {
public:
    Asterism ();
    Asterism (double point0_x, double point1_x, double point2_x, double point0_y, double point1_y, double point2_y);
    explicit Asterism (const std::vector<Point>& points);

    std::vector<Point> get_points () const;
    void set_points (const std::vector<Point>& new_points);
    const Point& operator[] (int index) const;
    bool operator== (const Asterism& other) const;

    void print () const;
    void print_xy () const;

private:
    std::vector<Point> points;
};


#endif //ASTERISM_VALIDATOR_ASTERISM_H