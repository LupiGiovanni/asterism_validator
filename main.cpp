#include "Asterism.h"
#include "Board.h"
#include "Board_set.h"
#include "Simulation.h"
#include "helper.h"
#include "dataset.h"
#include "Simulation_manager.h"
#include "Graphic_viewer.h"

int main () {
    Board_set bs;
    Graphic_viewer gv;
    // gv.draw(bs);
    // gv.draw(bs, cedric_dataset[0]);
    // gv.draw(bs, cedric_dataset[0], cedric_dataset[1]);
    // bs.assign_targets(cedric_dataset[0]);
    // bs.teleport(cedric_dataset[0]);
    // gv.draw(bs, cedric_dataset[0]);
    gv.animate(Movement::outside_technical_field, cedric_dataset[0]);
    gv.animate(Movement::linear_trajectory, cedric_dataset[3], cedric_dataset[5]);
}