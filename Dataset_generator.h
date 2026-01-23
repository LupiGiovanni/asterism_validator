//
// Created by gionimbus on 1/20/26.
//

#ifndef ASTERISM_VALIDATOR_DATASET_GENERATOR_H
#define ASTERISM_VALIDATOR_DATASET_GENERATOR_H

#include "Asterism.h"

constexpr int DATASET_SIZE = 1000;

class Dataset_generator {
public:
    std::vector<Asterism> dataset = {};

    void generate_random_valid_dataset ();

private:
    Asterism generate_random_asterism ();
    Asterism generate_random_valid_asterism ();
};


#endif //ASTERISM_VALIDATOR_DATASET_GENERATOR_H