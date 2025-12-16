//
// Created by gionimbus on 12/16/25.
//

#include "Asterism.h"

Asterism::Asterism(double ngs1_x, double ngs2_x, double ngs3_x, double ngs1_y, double ngs2_y, double ngs3_y) {
    ngs1 = Point(ngs1_x, ngs1_y);
    ngs2 = Point(ngs2_x, ngs2_y);
    ngs3 = Point(ngs3_x, ngs3_y);
}

