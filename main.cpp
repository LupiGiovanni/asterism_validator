#include "Asterism.h"
#include "Board.h"
#include "Board_set.h"
#include "Simulation.h"
#include "helper.h"
#include "dataset.h"
#include "Simulation_manager.h"
#include "Graphic_viewer.h"

int main () {
    Simulation_manager sm;
    sm.simulate_dataset(Movement::outside_technical_field, cedric_dataset);
    return 0;
}