cmake_minimum_required(VERSION 3.16)

project(LegoRaspiApi)



add_library(LegoRaspiApiLib SHARED
	"Command.cpp"
	HIDCon.cpp
	Brick.cpp
)

add_library(PubLeReAPI SHARED
	PubLeReAPI.cpp
)

target_link_libraries(PubLeReAPI PUBLIC LegoRaspiApiLib)

add_executable(LegoRaspiApiTest
	main.cpp
)

target_link_libraries(LegoRaspiApiTest LegoRaspiApiLib)

target_compile_features(LegoRaspiApiLib PUBLIC cxx_std_17)
target_compile_features(LegoRaspiApiTest PUBLIC cxx_std_17)
set_property(TARGET LegoRaspiApiLib PROPERTY CXX_STANDARD 17)
set_property(TARGET LegoRaspiApiTest PROPERTY CXX_STANDARD 17)