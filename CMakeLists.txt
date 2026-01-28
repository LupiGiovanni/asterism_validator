cmake_minimum_required(VERSION 4.0)

project(asterism_validator)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BUILD_TYPE Release)

find_package(CGAL REQUIRED OPTIONAL_COMPONENTS Qt6)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable (    asterism_validator
                    main.cpp
                    Board.cpp
                    Board.h
                    Asterism.cpp
                    Asterism.h
                    Board_set.cpp
                    Board_set.h
                    Simulation.cpp
                    Simulation.h
                    Dataset_generator.cpp
                    Dataset_generator.h
                    Simulation_manager.cpp
                    Simulation_manager.h
                    Graphic_viewer.cpp
                    Graphic_viewer.h
                    helper.h
                    dataset.h
                    coordinates.h   )

target_link_libraries(  asterism_validator
                        sfml-graphics
                        sfml-window
                        sfml-system  )

target_include_directories(asterism_validator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(asterism_validator CGAL::CGAL_Basic_viewer)

# TODO: remove Qt6 dependency if not needed