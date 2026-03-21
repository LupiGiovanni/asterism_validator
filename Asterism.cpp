//
// Created by gionimbus on 12/16/25.
//

#include "Asterism.h"

#include "State.h"

Asterism::Asterism(): ngs ( { Point(0.,0.), Point(0.,0.), Point(0.,0.) } ) {}

Asterism::Asterism(double ngs0_x, double ngs1_x, double ngs2_x, double ngs0_y, double ngs1_y, double ngs2_y):
    ngs{ Point(ngs0_x, ngs0_y), Point(ngs1_x, ngs1_y), Point(ngs2_x, ngs2_y) } {}

Asterism::Asterism(const std::vector<Point>& ngs_vector): ngs (ngs_vector) {}

std::vector<Point> Asterism::get_ngs_vector() const {
    return ngs;
}

//TODO: implement exception handling
Point Asterism::get_ngs(int index) const {
    return ngs[index];
}

void Asterism::print () const {
    std::cout << std::fixed << std::setprecision(DECIMAL_PLACES_PRINTED);
    std::cout << "{" << ngs[0].x() << ", " << ngs[1].x() << ", " << ngs[2].x() << ", " << ngs[0].y() << ", " << ngs[1].y() << ", " << ngs[2].y() << "}";
}

void Asterism::print_with_labels() const {
    std::cout << std::fixed << std::setprecision(DECIMAL_PLACES_PRINTED);
    std::cout << std::endl;
    std::cout << "ngs0_x\t\t\tngs1_x\t\t\tngs2_x\t\t\tngs0_y\t\t\tngs1_y\t\t\tngs2_y" << std::endl;
    std::cout << "------\t\t\t------\t\t\t------\t\t\t------\t\t\t------\t\t\t------" << std::endl;
    std::cout << ngs[0].x() << "\t\t" << ngs[1].x() << "\t\t" << ngs[2].x() << "\t\t" << ngs[0].y() << "\t\t" << ngs[1].y() << "\t\t" << ngs[2].y();
    std::cout << std::endl;
}

