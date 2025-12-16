cmake_minimum_required(VERSION 4.0)

project(asterism_validator)

set(CMAKE_CXX_STANDARD 20)

find_package(CGAL REQUIRED OPTIONAL_COMPONENTS Qt6)

add_executable(asterism_validator
                main.cpp
                Board.cpp Board.h)

target_link_libraries(asterism_validator CGAL::CGAL_Basic_viewer)
