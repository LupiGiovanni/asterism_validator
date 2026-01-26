//
// Created by gionimbus on 1/20/26.
//

#include "Dataset_generator.h"

const std::vector<Asterism>& Dataset_generator::get_dataset() const {
    return dataset;
}

Asterism Dataset_generator::generate_random_asterism() {
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

Asterism Dataset_generator::generate_random_valid_asterism () {
    Board_set temporary;
    Asterism new_asterism;
    do {
        new_asterism = generate_random_asterism();
        temporary.assign_targets(new_asterism);
    } while ( temporary.get_targets().empty() );

    return new_asterism;
}

void Dataset_generator::generate_random_valid_dataset() {
    dataset.clear();
    while (dataset.size() < GENERATED_DATASET_SIZE) {
        Asterism new_asterism = generate_random_valid_asterism();
        dataset.push_back(new_asterism);
    }
}