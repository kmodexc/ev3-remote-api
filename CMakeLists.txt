cmake_minimum_required(VERSION 3.16)
project(LegoRaspiApi)
#set(CMAKE_VERBOSE_MAKEFILE ON)

add_subdirectory(pybind11)
pybind11_add_module(legoapi 
	PubLeReAPI.cpp
	)
target_link_libraries(legoapi PUBLIC LegoRaspiApiLib)

#c++ library
find_package(Threads REQUIRED)
add_library(LegoRaspiApiLib SHARED
	"Command.cpp"
	HIDCon.cpp
	Brick.cpp
	Motor.cpp
	TouchSensor.cpp
	ColorSensor.cpp
)
target_link_libraries(LegoRaspiApiLib PUBLIC stdc++fs Threads::Threads)
target_compile_features(LegoRaspiApiLib PUBLIC cxx_std_17)

add_executable(test main.cpp)
target_link_libraries(test PUBLIC LegoRaspiApiLib)