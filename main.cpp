#include "Asterism.h"
#include "Board.h"
#include "Board_set.h"
#include "Simulation.h"
#include "helper.h"
#include "dataset.h"
#include "Simulation_manager.h"
#include "Graphic_viewer.h"
#include "A_star.h"

int main () {
    // State start (232.223713, 66.640670, -41.871824, 116.354008, -112.966366, -165.532668);
    // State goal (-64.074902, -38.632346, 216.687889, 107.928191, -10.634813, 132.970463);
    //
    // std::vector<State> path = A_star::search (start, goal);
    //
    // std::cout << "Path from start to goal:" << std::endl;
    // for (const auto& state : path)
    //     state.print();

    Asterism start_a (-76.305647, 158.618230, -136.754214, -36.137091, -111.701498, 217.041397);
    Asterism goal_a (122.718571, -33.932973, 249.711987, 36.378866, 260.887333, -54.757124);

    Asterism start_b (232.223713, 66.640670, -41.871824, 116.354008, -112.966366, -165.532668);
    Asterism goal_b (-64.074902, -38.632346, 216.687889, 107.928191, -10.634813, 132.970463);

    Asterism start_c {-139.814452, 78.426841, -9.328945, 202.766608, 219.972478, -264.680021};
    Asterism goal_c {-84.306862, 194.272736, -83.241414, -245.583848, 43.987158, 89.859614};

    Asterism start_d {135.306210, -158.253810, 47.627975, 211.535740, 191.990750, -197.778060};
    Asterism goal_d {177.373080, -124.148780, -165.782460, 19.419086, 171.931470, -127.961105};

    Asterism start_e {101.111560, -184.134550, 208.334800, 167.202600, -177.123410, -125.520910};
    Asterism goal_e {205.462480, -191.097690, -30.308712, -33.209840, 92.582100, -202.473850};

    Graphic_viewer gv;
    gv.animate(Movement::A_star, start_e, goal_e);
    // gv.animate(Movement::linear, start_c, goal_c);
    // Simulation_manager::simulate_dataset(Movement::linear, cedric_dataset);
    // Simulation_manager::simulate_dataset(Movement::A_star, cedric_dataset);

    //Simulation_manager::simulate_dataset_random(Movement::safe_basic);

    return 0;
}