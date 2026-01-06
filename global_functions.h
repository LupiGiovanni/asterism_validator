//
// Created by gionimbus on 12/16/25.
//

#ifndef ASTERISM_VALIDATOR_GLOBAL_FUNCTIONS_H
#define ASTERISM_VALIDATOR_GLOBAL_FUNCTIONS_H

#include <CGAL/Aff_transformation_2.h>
#include"Board.h"
#include"Asterism.h"

typedef CGAL::Aff_transformation_2<Kernel> Transformation;

inline void rotate (Polygon& polygon, double angle_radians) {
    Transformation rotation (CGAL::ROTATION, std::sin(angle_radians), std::cos(angle_radians));
    for (auto& vertex : polygon)
        vertex = rotation.transform(vertex);
}

inline void rotate (Point& point, double angle_radians) {
    Transformation rotation (CGAL::ROTATION, std::sin(angle_radians), std::cos(angle_radians));
    point = rotation.transform(point);
}

#endif //ASTERISM_VALIDATOR_GLOBAL_FUNCTIONS_H