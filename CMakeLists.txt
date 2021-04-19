cmake_minimum_required(VERSION 3.16)
project(LegoRaspiApi)
set(CMAKE_VERBOSE_MAKEFILE ON)

#c++ library
add_library(LegoRaspiApiLib SHARED
	"Command.cpp"
	HIDCon.cpp
	Brick.cpp
)
target_compile_features(LegoRaspiApiLib PUBLIC cxx_std_17)
set_property(TARGET LegoRaspiApiLib PROPERTY CXX_STANDARD_REQUIRED 17)
target_compile_options(LegoRaspiApiLib PRIVATE -std=c++17)

#python api
add_library(PubLeReAPI SHARED
	PubLeReAPI.cpp
)
target_compile_features(PubLeReAPI PUBLIC cxx_std_17)
set_property(TARGET LegoRaspiApiLib PROPERTY CXX_STANDARD_REQUIRED 17)
target_link_libraries(PubLeReAPI PUBLIC LegoRaspiApiLib)
target_compile_options(PubLeReAPI PRIVATE -std=c++17)

# tests
add_executable(LegoRaspiApiTest
	main.cpp
)
target_compile_features(LegoRaspiApiLib PUBLIC cxx_std_17)
target_link_libraries(LegoRaspiApiTest LegoRaspiApiLib)
set_property(TARGET LegoRaspiApiTest PROPERTY CXX_STANDARD_REQUIRED 17)
target_compile_options(LegoRaspiApiTest PRIVATE -std=c++17)
