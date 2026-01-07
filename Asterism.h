//
// Created by gionimbus on 12/16/25.
//

#ifndef ASTERISM_VALIDATOR_ASTERISM_H
#define ASTERISM_VALIDATOR_ASTERISM_H

#include "Board.h"

class Asterism {
public:
    Point ngs1;
    Point ngs2;
    Point ngs3;

    Asterism (double ngs1_x, double ngs2_x, double ngs3_x, double ngs1_y, double ngs2_y, double ngs3_y);
};


#endif //ASTERISM_VALIDATOR_ASTERISM_H