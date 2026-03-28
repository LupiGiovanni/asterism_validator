//
// Created by gionimbus on 1/20/26.
//

#ifndef ASTERISM_VALIDATOR_DATASET_GENERATOR_H
#define ASTERISM_VALIDATOR_DATASET_GENERATOR_H

#include "Asterism.h"

class Dataset_generator {
public:
    const std::vector<Asterism>& get_dataset () const;
    void generate_dataset_random_valid ();

private:
    std::vector<Asterism> dataset = {};

    Asterism generate_asterism_random ();
    Asterism generate_asterism_random_valid ();
};


#endif //ASTERISM_VALIDATOR_DATASET_GENERATOR_H