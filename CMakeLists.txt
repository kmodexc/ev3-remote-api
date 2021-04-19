cmake_minimum_required(VERSION 3.16)
project(LegoRaspiApi)
set(CMAKE_VERBOSE_MAKEFILE ON)

#c++ library
add_library(LegoRaspiApiLib SHARED
	"Command.cpp"
	HIDCon.cpp
	Brick.cpp
)
target_link_libraries(LegoRaspiApiLib PUBLIC stdc++fs)
target_compile_features(LegoRaspiApiLib PUBLIC cxx_std_17)

#python api
add_library(PubLeReAPI SHARED
	PubLeReAPI.cpp
)
target_compile_features(PubLeReAPI PUBLIC cxx_std_17)
target_link_libraries(PubLeReAPI PUBLIC LegoRaspiApiLib)

# tests
add_executable(LegoRaspiApiTest
	main.cpp
)
target_compile_features(LegoRaspiApiLib PUBLIC cxx_std_17)
target_link_libraries(LegoRaspiApiTest LegoRaspiApiLib)