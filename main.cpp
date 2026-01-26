#include "Asterism.h"
#include "Board.h"
#include "Board_set.h"
#include "Simulation.h"
#include "helper.h"
#include "dataset.h"
#include "Simulation_manager.h"

int main () {
    Simulation_manager::simulate_dataset(Movement::linear_trajectory, cedric_dataset);
    Simulation_manager::simulate_dataset(Movement::outside_technical_field, cedric_dataset);
}