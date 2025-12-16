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
    std::vector<Asterism> asterisms_not_valid {};
    std::vector<Asterism> asterisms_valid;

    for (auto asterism = dataset.begin(); asterism != dataset.end(); ++asterism) {
        count_total++;
        if (asterism->is_valid(board_1, board_2, board_3)) {
            count_valid++;
            asterisms_valid.push_back(*asterism);
        }
        else {
            count_not_valid++;
            asterisms_not_valid.push_back(*asterism);
        }
    }

    std::cout << "---------------------------------" << std::endl;
    std::cout << "Total NGS: " << count_total << std::endl;
    std::cout << "Valid NGSs: " << count_valid << std::endl;
    std::cout << "Not valid NGSs: " << count_not_valid << std::endl;

    for (auto asterism = asterisms_not_valid.begin(); asterism != asterisms_not_valid.end(); ++asterism) {
        draw(*asterism, board_1, board_2, board_3);
    }

    for (auto asterism = asterisms_valid.begin(); asterism != asterisms_valid.end(); ++asterism) {
        draw(*asterism, board_1, board_2, board_3);
    }
}