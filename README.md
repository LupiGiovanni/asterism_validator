# Asterism validator (and simulator)

Given XY coordinates of 3 Natural Guide Stars the program can establish if they are reachable by the LOR boards.

The program also simulates the movement of the LOR boards to reach the NGSs.

Libraries used are:
* CGAL (Computational Geometry Algorithms Library)
* SFML for graphic rendering
* sciplot for plotting histograms of dataset simulations

The program can be normally built with ```cmake``` and ```make```.

### Example of graphical output:
![Example of graphical output](include/boards_gif.gif)

### Example of main:
```c++
int main () {
    Simulation_manager::simulate_dataset(Movement::linear_trajectory, cedric_dataset);

    Graphic_viewer gv;
    gv.animate(Movement::linear_trajectory, cedric_dataset[0], cedric_dataset[1]);

    return 0;
}
```

### Example of command line output:
```c++
Simulation from point 170 to point 171 failed.

======================================================================================
                              Single simulation results                               

> Movement type		        linear trajectory
> Start asterism	        {156.558380, -100.301720, -23.493893, 165.580800, -230.937740, -199.302780}
> Start valid		        true
> Destination asterism	    {190.285700, -142.410190, -98.780200, 89.886894, 180.640180, -153.202710}
> Destination valid	        true

> Boards cruise velocity	10.000000 mm/s
> Movement duration		    0.450000 seconds
> Simulation iterations		9
> Max iterations exceeded	false
> Iteration time step		0.050000 seconds
> Iteration distance step	0.500000 mm
> Destination reached		false
> Distance from dest		inf
> Collision detected		true
> FoV small vignetting		false
> FoV large vignetting		false
======================================================================================

======================================================================================
                             Dataset simulations results                              

> Movement type			    linear trajectory
> Boards cruise velocity	10.000000 mm/s
> Total simulations		    333
> Successful simulations	331
> Average duration		    26.694864 s
======================================================================================
```

### Example of histogram output:
![Example of histogram output](include/histogram.png)