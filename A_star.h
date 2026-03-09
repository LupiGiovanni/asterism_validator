//
// Created by gionimbus on 3/9/26.
//

#ifndef ASTERISM_VALIDATOR_A_STAR_H
#define ASTERISM_VALIDATOR_A_STAR_H

#include <vector>
#include "Node.h"
#include "Board_set.h"

class A_star {
public:
    std::vector<Node> search (const Node& start, const Node& goal);

private:
    std::vector<Node> get_neighbors(const Node& node) const;
    unsigned long calculate_h (const Node& current, const Node& goal);
};


#endif //ASTERISM_VALIDATOR_A_STAR_H