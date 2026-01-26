//
// Created by gionimbus on 12/16/25.
//

#ifndef ASTERISM_VALIDATOR_ASTERISM_H
#define ASTERISM_VALIDATOR_ASTERISM_H

#include "Board.h"

class Asterism {
public:
    Asterism();

    Asterism (double ngs0_x, double ngs1_x, double ngs2_x, double ngs0_y, double ngs1_y, double ngs2_y);

    explicit Asterism (const std::vector<Point>& ngs_vector);

    std::vector<Point> get_ngs_vector() const;

    Point get_ngs(int index) const;

    void print() const;

private:
    std::vector<Point> ngs;
};


#endif //ASTERISM_VALIDATOR_ASTERISM_H