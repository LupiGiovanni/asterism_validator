# Asterism validator

Given XY coordinates of 3 Natural Guide Stars the program establishes if they are reachable by the LOR boards (without collisions).

The program uses CGAL (Computational Geometry Algorithms Library) and Qt6 for graphic rendering.

~~~bash
sudo apt upgrade
sudo apt install build-essential cmake g++ libboost-all-dev libcgal-dev qt6-base-dev qt6-tools-dev
~~~

Then the program can be normally built with ```cmake``` and ```make```.

---

To draw a graphical result, use the high-level function 

~~~cpp
draw (const Asterism& asterism, Board& board_1, Board& board_2, Board& board_3)
~~~

Note that the ```draw``` function can cause problems if used in very long loops.<br>
Use ```w``` key to disable area coloring of the drawn polygons.