#include <iostream>
#include "dataset.h"
#include "global_functions.h"
#include "Board.h"
#include "Asterism.h"

int main() {
    Board board_1 (Board_type::type_1);
    Board board_2 (Board_type::type_2);
    Board board_3 (Board_type::type_3);

    int total = 0;
    int valid = 0;
    int not_valid = 0;
    std::vector<Asterism> asterisms_not_valid {};

    for (auto asterism = dataset.begin(); asterism != dataset.end(); ++asterism) {
        total++;
        if (asterism->is_valid(board_1, board_2, board_3)) {
            valid++;
            std::cout << "Valid" << std::endl;
        }
        else {
            not_valid++;
            asterisms_not_valid.push_back(*asterism);
            std::cout << "Not valid";
        }
    }

    std::cout << "---------------------------------" << std::endl;
    std::cout << "Total NGS: " << total << std::endl;
    std::cout << "Valid NGSs: " << valid << std::endl;
    std::cout << "Not valid NGSs: " << not_valid << std::endl;

    for (auto asterism = asterisms_not_valid.begin(); asterism != asterisms_not_valid.end(); ++asterism) {
        draw(*asterism, board_1, board_2, board_3);
    }
}