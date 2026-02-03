#include "Asterism.h"
#include "Board.h"
#include "Board_set.h"
#include "Simulation.h"
#include "helper.h"
#include "dataset.h"
#include "Simulation_manager.h"
#include "Graphic_viewer.h"
#include "Trajectory_generator.h"

int main () {
    Asterism start_asterism (55.713890, 10.889601, 40.985504, 130.928414, 240.267069, -80.694414);
    Asterism destination_asterism (-37.754855, 10.074834, -142.597735, 143.916200, -206.395374, -84.891898);
    Board_set board_set;
    Graphic_viewer gv;
    board_set.assign_targets(start_asterism);
    board_set.teleport(start_asterism);
    gv.draw(board_set, start_asterism, destination_asterism);
    Trajectory_generator tg(board_set);
    tg.generate_trajectory(0, start_asterism.get_ngs(1), destination_asterism.get_ngs(1));
    std::vector<Point> trajectory = tg.get_trajectory();
    for (const auto& point : trajectory) {
        std::cout << "(" << point.x() << ", " << point.y() << ")" << std::endl;
    }
    gv.animate_trajectory(board_set, 0, trajectory);
    return 0;
}