//
// Created by gionimbus on 12/16/25.
//

#ifndef ASTERISM_VALIDATOR_ASTERISM_H
#define ASTERISM_VALIDATOR_ASTERISM_H

#include "Board.h"

// Represents a set of 3 natural guide stars (ngs)
class Asterism {
public:
    Point ngs1;
    Point ngs2;
    Point ngs3;

    // The default constructor creates an asterism with all ngs coordinates set to zero
    Asterism ();
    Asterism (double ngs1_x, double ngs2_x, double ngs3_x, double ngs1_y, double ngs2_y, double ngs3_y);
    explicit Asterism (const std::vector<Point>& ngs_vector);

    bool operator == (const Asterism& asterism) const;

    //Prints ngs coordinates
    void print() const;
};


#endif //ASTERISM_VALIDATOR_ASTERISM_H