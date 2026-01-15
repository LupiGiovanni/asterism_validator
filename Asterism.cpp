//
// Created by gionimbus on 12/16/25.
//

#include <iostream>
#include <iomanip>
#include "helper.h"
#include "Asterism.h"

Asterism::Asterism(): ngs1(Point(0.,0.)), ngs2(Point(0.,0.)), ngs3(Point(0.,0.)) {}

Asterism::Asterism(double ngs1_x, double ngs2_x, double ngs3_x, double ngs1_y, double ngs2_y, double ngs3_y):
    ngs1(Point(ngs1_x, ngs1_y)),
    ngs2(Point(ngs2_x, ngs2_y)),
    ngs3(Point(ngs3_x, ngs3_y)) {}

bool Asterism::operator == (const Asterism& asterism) const {
    if (ngs1 == asterism.ngs1 && ngs2 == asterism.ngs2 && ngs3 == asterism.ngs3)
        return true;
    return false;
}

void Asterism::print () const {
    std::cout << std::fixed << std::setprecision(DECIMAL_PLACES_PRINTED);
    std::cout << "{" << ngs1.x() << ", " << ngs2.x() << ", " << ngs3.x() << ", " << ngs1.y() << ", " << ngs2.y() << ", " << ngs3.y() << "}";
}

