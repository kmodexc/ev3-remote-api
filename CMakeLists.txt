cmake_minimum_required(VERSION 3.16)
project(LegoRaspiApi)
#set(CMAKE_VERBOSE_MAKEFILE ON)

add_subdirectory(pybind11)
add_subdirectory(IO)
add_subdirectory(Lego)
add_subdirectory(PybricksWrapper)
add_subdirectory(tests)