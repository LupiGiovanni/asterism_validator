#include <iostream>
#include "dataset.h"
#include "global_functions.h"
#include "Board.h"
#include "Board_set.h"
#include "Asterism.h"

int main() {
    Board_set boards;
    boards.draw(dataset[0]);
    return 0;
}