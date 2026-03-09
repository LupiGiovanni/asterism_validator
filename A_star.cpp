//
// Created by gionimbus on 3/9/26.
//

#include "A_star.h"

std::vector<Node> A_star::get_neighbors (const Node& node) const {

}

unsigned long A_star::calculate_h(const Node& current, const Node& goal) {
    unsigned long dx = (current.x > goal.x) ? (current.x - goal.x) : (goal.x - current.x);
    unsigned long dy = (current.y > goal.y) ? (current.y - goal.y) : (goal.y - current.y);

    if (dx < dy)
        return 14 * dx + 10 * (dy - dx);

    return 14 * dy + 10 * (dx - dy);
}