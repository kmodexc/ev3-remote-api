cmake_minimum_required(VERSION 3.16)
add_executable(test main.cpp)
target_link_libraries(test PUBLIC LegoRaspiApiLib)
target_include_directories(test PUBLIC ../PybricksWrapper)