cmake_minimum_required(VERSION 3.16)

add_library(LegoRaspiApiLib SHARED	
    ColorSensor.cpp
    GyroSensor.cpp
    Motor.cpp
    TouchSensor.cpp
    UltrasonicSensor.cpp
)
target_link_libraries(LegoRaspiApiLib PUBLIC Lego)
target_include_directories(LegoRaspiApiLib PUBLIC ../Lego)

pybind11_add_module(legoapi 
	PubLeReAPI.cpp
	)
target_link_libraries(legoapi PUBLIC LegoRaspiApiLib)
target_include_directories(legoapi PUBLIC ../pybind11/include)