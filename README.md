# Asterism validator

Given XY coordinates of 3 Natural Guide Stars the program establishes if they are reachable by the LOR boards (without collisions).

The program also can simulate the movement of the LOR boards to reach the NGSs.

The program uses CGAL (Computational Geometry Algorithms Library) and Qt6 for graphic rendering.

~~~bash
sudo apt upgrade
sudo apt install build-essential cmake g++ libboost-all-dev libcgal-dev qt6-base-dev qt6-tools-dev
~~~

Then the program can be normally built with ```cmake``` and ```make```.