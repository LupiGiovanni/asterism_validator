//
// Created by gionimbus on 1/26/26.
//

#include "Simulation_manager.h"

void Simulation_manager::simulate_dataset (Movement movement_type, const std::vector<Asterism>& dataset) {
    switch ( movement_type ) {
        case Movement::linear_trajectory:
            simulate_dataset_linear_trajectory(dataset);
            break;
        case Movement::outside_technical_field:
            simulate_dataset_outside_tech_field(dataset);
            break;
        case Movement::none:
            std::cout << "Warning: attempted to run dataset simulation but 'movement_type' is 'none'" << std::endl;
            break;
    }
}

void Simulation_manager::simulate_random_dataset(Movement movement_type) {
    Dataset_generator dg;
    dg.generate_random_valid_dataset();
    simulate_dataset(movement_type, dg.get_dataset());
}

void Simulation_manager::simulate_dataset_linear_trajectory(const std::vector<Asterism> &dataset) {
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
        simulation.run(Movement::linear_trajectory,boards, dataset[i-1], dataset[i]);
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
        else if (simulation.is_start_valid() && simulation.is_destination_valid()) {
            std::cout << "Simulation from point " << i-1 << " to point " << i << " failed." << std::endl;
            simulation.print_results();

            //============================================================================================
            // VISUALIZATION FOR DEBUGGING TODO: REMOVE LATER
            // Graphic_viewer gv;
            // gv.animate(Movement::linear_trajectory, dataset[i-1], dataset[i]);
            //============================================================================================
        }
    }

    print_results(Movement::linear_trajectory, total_simulations, successful_simulations, durations_sum);
    print_histogram(y_values);
}

void Simulation_manager::simulate_dataset_outside_tech_field(const std::vector<Asterism> &dataset) {
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
        else if (simulation.is_start_valid()) {
            std::cout << "Simulation from point " << i << " failed." << std::endl;
            simulation.print_results();

            //============================================================================================
            // VISUALIZATION FOR DEBUGGING TODO: REMOVE LATER
            // Graphic_viewer gv;
            // gv.animate(Movement::outside_technical_field, dataset[i]);
            //============================================================================================
        }
    }

    print_results(Movement::outside_technical_field, total_simulations, successful_simulations, durations_sum);
    print_histogram(y_values);
}

void Simulation_manager::print_results(Movement movement_type, int total_simulations, int successful_simulations, double durations_sum) {
    std::cout << std::fixed << std::setprecision(DECIMAL_PLACES_PRINTED);

    std::string movement_type_str = (movement_type == Movement::linear_trajectory) ? "linear trajectory" : "outside technical field";

    std::cout << std::endl;
    std::cout << "======================================================================================" << std::endl;
    std::cout << "                             Dataset simulations results                              " << std::endl;
    std::cout << std::endl;
    std::cout << "> Movement type\t\t\t\t" << movement_type_str << std::endl;
    std::cout << "> Boards cruise velocity\t"<< BOARD_VELOCITY << " mm/s" << std::endl;
    std::cout << "> Total simulations\t\t\t" << total_simulations << std::endl;
    std::cout << "> Successful simulations\t" << successful_simulations << std::endl;
    std::cout << "> Average duration\t\t\t" << (durations_sum / successful_simulations) << " seconds" << std::endl;
    std::cout << "======================================================================================" << std::endl;
    std::cout << std::endl;
}

void Simulation_manager::insert_into_histogram(std::array<int, HISTOGRAM_INTERVALS_COUNT>& y_values, double duration) {
    for (int i = 0; i < HISTOGRAM_INTERVALS_COUNT - 1; ++i) {
        if (duration <= ( i * 10 + 10 )) {
            y_values[i]++;
            break;
        }
    }
    if (duration > (HISTOGRAM_INTERVALS_COUNT - 1) * 10 )
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
    histogram.drawBoxes(x_labels, y_values).fillSolid().fillColor("blue").fillIntensity(0.7).labelNone();

    sciplot::Figure fig = {{histogram}};
    sciplot::Canvas canvas = {{fig}};
    canvas.size(1000, 600);
    canvas.show();
}