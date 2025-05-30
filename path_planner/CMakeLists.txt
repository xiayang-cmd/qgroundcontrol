cmake_minimum_required(VERSION 3.10)
project(PathPlanner)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(planner
    src/AreaGridPlanner.cpp
    src/CorridorStripPlanner.cpp)

add_executable(test_planner
    tests/test_planner.cpp)

target_link_libraries(test_planner planner)
