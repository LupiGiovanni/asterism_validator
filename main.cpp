#include <iostream>
#include "dataset.h"
#include "global_functions.h"
#include "Board.h"
#include "Asterism.h"

int main() {
    Board board_1 (Board_type::type_1);
    Board board_2 (Board_type::type_2);
    Board board_3 (Board_type::type_3);

    int count_total = 0;
    int count_valid = 0;
    int count_not_valid = 0;

    std::vector<Asterism> not_valid;

    for (auto asterism = dataset.begin(); asterism != dataset.end(); ++asterism) {
        count_total++;
        if (asterism->is_valid(board_1, board_2, board_3)) {
            count_valid++;
            //draw(*asterism, board_1, board_2, board_3);
        }
        else {
            count_not_valid++;
            //draw(*asterism, board_1, board_2, board_3);
            not_valid.push_back(*asterism);
        }
    }

    std::cout << "---------------------------------" << std::endl;
    std::cout << "Total NGSs: " << count_total << std::endl;
    std::cout << "Valid NGSs: " << count_valid << std::endl;
    std::cout << "Not valid NGSs: " << count_not_valid << std::endl << std::endl;

   for (auto asterism = not_valid.begin(); asterism != not_valid.end(); ++asterism) {
        std::cout << "{"
                  << asterism->ngs1.x() << ","
                  << asterism->ngs2.x() << ","
                  << asterism->ngs3.x() << ","
                  << asterism->ngs1.y() << ","
                  << asterism->ngs2.y() << ","
                  << asterism->ngs3.y()
                  << "}"
                  << std::endl;
    }

    Asterism a = Asterism {223.753,-221.749,120.923,-51.515,-102.595,-182.088};
    a.is_valid(board_1, board_2, board_3);
    draw(a, board_1, board_2, board_3);

    return 0;
}