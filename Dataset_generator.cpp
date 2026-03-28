//
// Created by gionimbus on 1/20/26.
//

#include <random>
#include "Board_set.h"
#include "Dataset_generator.h"

const std::vector<Asterism>& Dataset_generator::get_dataset() const {
    return dataset;
}

Asterism Dataset_generator::generate_asterism_random() {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    double radius = TECHNICAL_FIELD_RADIUS;
    double radius_squared = radius * radius;
    std::uniform_real_distribution<> dis(-radius, radius);

    int num_ngs = 3;
    std::vector<Point> ngs;

    while (ngs.size() < num_ngs) {
        double x = dis(gen);
        double y = dis(gen);

        if (x*x + y*y <= radius_squared)
            ngs.push_back({x, y});
    }

    return Asterism(ngs);
}

Asterism Dataset_generator::generate_asterism_random_valid () {
    Board_set temporary;
    Asterism new_asterism;
    do {
        new_asterism = generate_asterism_random();
        temporary.assign_targets(new_asterism);
    } while ( temporary.get_targets().empty() );

    return new_asterism;
}

void Dataset_generator::generate_dataset_random_valid() {
    dataset.clear();
    while (dataset.size() < GENERATED_DATASET_SIZE) {
        Asterism new_asterism = generate_asterism_random_valid();
        dataset.push_back(new_asterism);
    }
}