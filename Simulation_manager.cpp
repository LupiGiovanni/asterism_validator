//
// Created by gionimbus on 1/26/26.
//

#include "Simulation_manager.h"

void Simulation_manager::simulate_dataset (Movement movement_type, const std::vector<Asterism>& dataset) {
    switch ( movement_type ) {
        case Movement::linear_trajectory:
            simulate_dataset_helper(movement_type, dataset);
            break;
        case Movement::safe_basic:
            simulate_dataset_helper(movement_type, dataset);
            break;
        case Movement::outside_technical_field:
            simulate_dataset_outside_tech_field(dataset);
            break;
        case Movement::none:
            std::cout << "Warning: attempted to run dataset simulation but 'movement_type' is 'none'" << std::endl;
            break;
    }
}

void Simulation_manager::simulate_dataset_random(Movement movement_type) {
    Dataset_generator dg;
    dg.generate_dataset_random_valid();
    simulate_dataset(movement_type, dg.get_dataset());
}

void Simulation_manager::simulate_dataset_helper(Movement movement_type, const std::vector<Asterism> &dataset) {
    if ( dataset.empty() ) {
        std::cout << "Warning: attempted to run dataset simulation but 'dataset' vector is empty" << std::endl;
        return;
    }

    Board_set boards;
    Simulation simulation;

    int total_simulations = 0;
    int successful_simulations = 0;
    double durations_sum = 0.;
    std::array<int, HISTOGRAM_INTERVALS_COUNT> y_values = {0};

    for (int i = 1; i < dataset.size(); ++i) {
        simulation.run(movement_type,boards, dataset[i-1], dataset[i]);
        total_simulations++;
        if (simulation.is_destination_reached() && !simulation.is_collision_detected()) {
            successful_simulations++;
            durations_sum += simulation.get_duration();
            insert_into_histogram(y_values, simulation.get_duration());

            //============================================================================================
            // VISUALIZATION FOR DEBUGGING TODO: REMOVE LATER
            // Graphic_viewer gv;
            // gv.animate(movement_type, dataset[i-1], dataset[i]);
            //============================================================================================
        }
        else {
            std::cout << std::endl;
            std::cout << "Simulation from asterism " << i-1 << " to asterism " << i << " of the dataset failed. Detailed info below: ";
            std::cout << std::endl;
            simulation.print_results();

            //============================================================================================
            // VISUALIZATION FOR DEBUGGING TODO: REMOVE LATER
            // Graphic_viewer gv;
            // gv.animate(movement_type, dataset[i-1], dataset[i]);
            //============================================================================================
        }
    }

    print_results(dataset, movement_type, total_simulations, successful_simulations, durations_sum);
    print_histogram(y_values);
}

void Simulation_manager::simulate_dataset_outside_tech_field(const std::vector<Asterism>& dataset) {
    if ( dataset.empty() ) {
        std::cout << "Warning: attempted to run dataset simulation but 'dataset' vector is empty" << std::endl;
        return;
    }

    Board_set boards;
    Simulation simulation;

    int total_simulations = 0;
    int successful_simulations = 0;
    double durations_sum = 0.;
    std::array<int, HISTOGRAM_INTERVALS_COUNT> y_values = {0};

    for (int i = 0; i < dataset.size(); ++i) {
        simulation.run(Movement::outside_technical_field, boards, dataset[i]);
        total_simulations++;
        if (simulation.is_destination_reached() && !simulation.is_collision_detected()) {
            successful_simulations++;
            durations_sum += simulation.get_duration();
            insert_into_histogram(y_values, simulation.get_duration());

            //============================================================================================
            // VISUALIZATION FOR DEBUGGING TODO: REMOVE LATER
            // Graphic_viewer gv;
            // gv.animate(Movement::outside_technical_field, dataset[i]);
            //============================================================================================
        }
        else {
            std::cout << std::endl;
            std::cout << "Simulation from asterism " << i << " of the dataset failed. Detailed info below: " ;
            std::cout << std::endl;
            simulation.print_results();

            //============================================================================================
            // VISUALIZATION FOR DEBUGGING TODO: REMOVE LATER
            // Graphic_viewer gv;
            // gv.animate(Movement::outside_technical_field, dataset[i]);
            //============================================================================================
        }
    }

    print_results(dataset, Movement::outside_technical_field, total_simulations, successful_simulations, durations_sum);
    print_histogram(y_values);
}

void Simulation_manager::simulate(Movement movement_type, const Asterism& start, const Asterism& destination) {
    Board_set boards;
    Simulation simulation;

    simulation.run(movement_type, boards, start, destination);
    simulation.print_results();
}

void Simulation_manager::print_results(const std::vector<Asterism>& dataset, Movement movement_type, int total_simulations, int successful_simulations, double durations_sum) {
    std::cout << std::fixed << std::setprecision(DECIMAL_PLACES_PRINTED);

    std::string movement_type_str;
    switch (movement_type) {
        case Movement::linear_trajectory:
            movement_type_str = "linear trajectory";
            break;
        case Movement::safe_basic:
            movement_type_str = "safe basic";
            break;
        case Movement::outside_technical_field:
            movement_type_str = "outside technical field";
            break;
        case Movement::none:
            movement_type_str = "none";
            break;
    }

    std::cout << std::endl;
    std::cout << "/////////////////////////////////////////////////////////////////////////////////////////////////////////" << std::endl;
    std::cout << "                                      Dataset simulations results                                       " << std::endl;
    std::cout << std::endl;
    std::cout << "> Movement type\t\t\t\t" << movement_type_str << std::endl;
    std::cout << "> Boards cruise velocity\t"<< BOARD_VELOCITY << " mm/s" << std::endl;
    std::cout << "> Dataset size\t\t\t\t" << dataset.size() << " asterisms" << std::endl;
    std::cout << "> Total simulations\t\t\t" << total_simulations << std::endl;
    std::cout << "> Successful simulations\t" << successful_simulations << std::endl;
    std::cout << "> Success rate\t\t\t\t" << (100. * successful_simulations / total_simulations) << " %" << std::endl;
    std::cout << "> Avg successful duration\t" << (durations_sum / successful_simulations) << " s" << std::endl;
    std::cout << "/////////////////////////////////////////////////////////////////////////////////////////////////////////" << std::endl;
    std::cout << std::endl;
}

void Simulation_manager::insert_into_histogram(std::array<int, HISTOGRAM_INTERVALS_COUNT>& y_values, double value) {
    for (int i = 0; i < HISTOGRAM_INTERVALS_COUNT - 1; ++i) {
        if (value <= ( i * 10 + 10 )) {
            y_values[i]++;
            break;
        }
    }
    if (value > (HISTOGRAM_INTERVALS_COUNT - 1) * 10 )
        y_values[HISTOGRAM_INTERVALS_COUNT - 1]++;
}

void Simulation_manager::print_histogram(const std::array<int, HISTOGRAM_INTERVALS_COUNT>& y_values) {
    sciplot::Strings x_labels(HISTOGRAM_INTERVALS_COUNT);

    for (int i = 0; i < HISTOGRAM_INTERVALS_COUNT - 1; ++i)
        x_labels[i] = std::to_string(i * 10) + "-" + std::to_string(i * 10 + 10);

    x_labels[HISTOGRAM_INTERVALS_COUNT - 1] = ">" + std::to_string((HISTOGRAM_INTERVALS_COUNT - 1) * 10);

    sciplot::Vec y_count (HISTOGRAM_INTERVALS_COUNT);
    for (int i = 0; i < HISTOGRAM_INTERVALS_COUNT; ++i)
        y_count[i] = y_values[i];

    sciplot::Plot2D histogram;

    histogram.xlabel("Duration (s)").fontSize(HISTOGRAM_FONT_SIZE);
    histogram.xtics().fontSize(HISTOGRAM_FONT_SIZE);
    histogram.ylabel("Count").fontSize(HISTOGRAM_FONT_SIZE);
    histogram.ytics().fontSize(HISTOGRAM_FONT_SIZE);
    histogram.boxWidthRelative(0.65);
    histogram.grid().ytics().show(true);
    histogram.legend().show(false);
    histogram.drawBoxes(x_labels, y_values).fillSolid().fillColor("blue").fillIntensity(0.5).borderShow(5).labelNone();

    sciplot::Figure fig = {{histogram}};
    sciplot::Canvas canvas = {{fig}};
    canvas.size(1000, 600);
    canvas.show();
}