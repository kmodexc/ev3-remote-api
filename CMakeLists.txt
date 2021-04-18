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

target_compile_features(LegoRaspiApiLib PRIVATE cxx_std_17)